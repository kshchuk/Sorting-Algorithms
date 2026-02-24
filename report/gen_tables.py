#!/usr/bin/env python3
"""Generate LaTeX longtable rows from CSV (type,algorithm,condition,N,V_bytes,K,T_ms)."""
import csv
import sys
from pathlib import Path

COND_UA = {"Worst": "Найгірший", "Uniform": "Рівномірний", "Normal": "Нормальний", "Best": "Найкращий"}

def tex(s):
    return s.replace("_", "\\_")

HEADER = ["type", "algorithm", "condition", "N", "V_bytes", "K", "T_ms"]

def load_rows(path):
    rows = []
    with open(path, newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f, fieldnames=HEADER):
            if r.get("type") and r.get("algorithm") and (r.get("N") or "").isdigit():
                rows.append(r)
    return rows

def format_num(x):
    try:
        v = int(float(x))
        if v >= 1_000_000:
            return f"{v/1e6:.1f}M" if v % 1_000_000 == 0 else f"{v/1e6:.2f}M"
        if v >= 1_000:
            return f"{v/1e3:.1f}K" if v % 1000 == 0 else f"{v/1e3:.2f}K"
        return str(v)
    except (ValueError, TypeError):
        return str(x)

def format_T(x):
    try:
        t = float(x)
        if t >= 1000:
            return f"{t:.0f}"
        if t >= 1:
            return f"{t:.2f}"
        if t >= 0.001:
            return f"{t:.4f}"
        return f"{t:.2e}"
    except (ValueError, TypeError):
        return str(x)

def gen_tables(rows, data_type, ns=None):
    if ns is None:
        ns = sorted(set(int(r["N"]) for r in rows))
    lines = []
    for n in ns:
        sub = [r for r in rows if int(r["N"]) == n]
        if not sub:
            continue
        lines.append("\\subsection*{%s, $N = %s$}" % (data_type, format_num(str(n))))
        lines.append("\\begin{center}")
        lines.append("\\small")
        lines.append("\\begin{longtable}{llrrr}")
        lines.append("\\toprule")
        lines.append("Алгоритм & Умова & V (Б) & K & T (мс) \\\\")
        lines.append("\\midrule")
        lines.append("\\endfirsthead")
        lines.append("\\multicolumn{5}{l}{(продовження)} \\\\")
        lines.append("\\toprule")
        lines.append("Алгоритм & Умова & V (Б) & K & T (мс) \\\\")
        lines.append("\\midrule")
        lines.append("\\endhead")
        for r in sub:
            algo = tex(r["algorithm"])
            cond = COND_UA.get(r["condition"], r["condition"])
            v = r["V_bytes"].strip()
            k = format_num(r["K"])
            t = format_T(r["T_ms"])
            lines.append("%s & %s & %s & %s & %s \\\\" % (algo, cond, v, k, t))
        lines.append("\\bottomrule")
        lines.append("\\end{longtable}")
        lines.append("\\end{center}")
        lines.append("")
    return "\n".join(lines)

def main():
    report_dir = Path(__file__).resolve().parent
    for name, csv_name in [("int", "data_int.csv"), ("double", "data_double.csv")]:
        path = report_dir / csv_name
        if not path.exists():
            print("Skip (no file):", path, file=sys.stderr)
            continue
        rows = load_rows(path)
        if not rows:
            continue
        ns = [10000, 20000, 50000, 100000, 200000, 500000, 1000000]
        out = report_dir / ("tables_%s.tex" % name)
        title = "int" if name == "int" else "double"
        with open(out, "w", encoding="utf-8") as f:
            f.write(gen_tables(rows, title, ns))
        print("Wrote", out)

if __name__ == "__main__":
    main()

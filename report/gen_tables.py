#!/usr/bin/env python3
"""Generate LaTeX longtable rows from CSV (type,algorithm,condition,N,V_bytes,K,T_ms).
   Optional: merge benchmark overlay (real_time, BigO) from Google Benchmark log for int."""
import csv
import re
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

def parse_benchmark_log(path):
    """Parse BM_Sort/sorting::Algo/Condition/N/real_time and .../real_time_BigO lines.
    Returns (t_map, bigo_map): t_map[(algo,cond,N)] = T_ms, bigo_map[(algo,cond)] = BigO string."""
    t_map = {}
    bigo_map = {}
    pat_time = re.compile(r"BM_Sort/sorting::([^/]+)/([^/]+)/(\d+)/real_time\s+([\d.]+)\s*ms")
    pat_bigo = re.compile(r"BM_Sort/sorting::([^/]+)/([^/]+)/real_time_BigO\s+([\d.]+)\s+(\S+)")
    with open(path, encoding="utf-8") as f:
        for line in f:
            m = pat_time.search(line)
            if m:
                algo, cond, n, t = m.group(1), m.group(2), int(m.group(3)), float(m.group(4))
                t_map[(algo, cond, n)] = t
                continue
            m = pat_bigo.search(line)
            if m:
                algo, cond = m.group(1), m.group(2)
                bigo_map[(algo, cond)] = m.group(3) + " " + m.group(4)
    return t_map, bigo_map

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

def gen_tables(rows, data_type, ns=None, overlay=None):
    """overlay = (t_map, bigo_map) from parse_benchmark_log; used only for int."""
    if ns is None:
        ns = sorted(set(int(r["N"]) for r in rows))
    use_overlay = data_type == "int" and overlay is not None
    t_map, bigo_map = overlay if overlay else ({}, {})
    cols = "llrrrl" if use_overlay else "llrrr"
    header = "Алгоритм & Умова & V (Б) & K & T (мс) & BigO \\\\" if use_overlay else "Алгоритм & Умова & V (Б) & K & T (мс) \\\\"
    lines = []
    for n in ns:
        sub = [r for r in rows if int(r["N"]) == n]
        if not sub:
            continue
        lines.append("\\subsection*{%s, $N = %s$}" % (data_type, format_num(str(n))))
        lines.append("\\begin{center}")
        lines.append("\\small")
        lines.append("\\begin{longtable}{%s}" % cols)
        lines.append("\\toprule")
        lines.append(header)
        lines.append("\\midrule")
        lines.append("\\endfirsthead")
        lines.append("\\multicolumn{%d}{l}{(продовження)} \\\\" % (6 if use_overlay else 5))
        lines.append("\\toprule")
        lines.append(header)
        lines.append("\\midrule")
        lines.append("\\endhead")
        for r in sub:
            algo_key = r["algorithm"]
            cond_key = r["condition"]
            algo = tex(algo_key)
            cond = COND_UA.get(cond_key, cond_key)
            v = r["V_bytes"].strip()
            k = format_num(r["K"])
            t_val = t_map.get((algo_key, cond_key, n), r["T_ms"])
            t = format_T(str(t_val))
            if use_overlay:
                bigo = bigo_map.get((algo_key, cond_key), "---")
                bigo_tex = ("$%s$" % bigo) if bigo != "---" else "---"
                lines.append("%s & %s & %s & %s & %s & %s \\\\" % (algo, cond, v, k, t, bigo_tex))
            else:
                lines.append("%s & %s & %s & %s & %s \\\\" % (algo, cond, v, k, t))
        lines.append("\\bottomrule")
        lines.append("\\end{longtable}")
        lines.append("\\end{center}")
        lines.append("")
    return "\n".join(lines)

def main():
    report_dir = Path(__file__).resolve().parent
    overlay = None
    bench_path = report_dir / "benchmark_log.txt"
    if len(sys.argv) > 1:
        bench_path = Path(sys.argv[1])
    if bench_path.exists():
        try:
            overlay = parse_benchmark_log(bench_path)
            print("Loaded benchmark overlay from", bench_path, file=sys.stderr)
        except Exception as e:
            print("Benchmark overlay parse failed:", e, file=sys.stderr)
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
            f.write(gen_tables(rows, title, ns, overlay=overlay if name == "int" else None))
        print("Wrote", out)

if __name__ == "__main__":
    main()

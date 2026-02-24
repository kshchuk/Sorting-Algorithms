# Sorting Algorithms

C++ implementations of sorting algorithms with benchmarks and tests.

## Звіт (Лабораторний проєкт 1, ОС)

Звіт у форматі LaTeX знаходиться в каталозі **`report/`**:

- **`report/report.tex`** — вихідний текст звіту (Кіщук Ярослав Ярославович).
- **`report/report.pdf`** — зібраний PDF (після збірки: `cd report && pdflatex report.tex`).

Структура звіту:

1. **Мета роботи** — опанувати реалізацію та експериментальне дослідження алгоритмів сортування, порівняти їх за часом, кількістю порівнянь і пам’яттю.
2. **Завдання** — реалізація алгоритмів для `int`/`double`, оцінка V, K, T, експерименти для N від 10⁴ до 10⁶, чотири умови даних.
3. **Теоретична складність** — оцінки O(·) для всіх алгоритмів (Insertion, Quick, Merge, Heap, Bubble, Selection, Shell, Radix, Counting та багатопотокові варіанти).
4. **Таблиці результатів** — вимірювання за типом `int` та `double` (longtable за N).
5. **Висновок** — порівняння швидкодії, пам’яті, відповідність теорії; рекомендації щодо вибору алгоритму.
6. **Код і скріни** — посилання на репозиторій, скріншоти консолі та GUI, графіки залежності часу від N.

Дані для таблиць зберігаються в `report/data_int.csv` та `report/data_double.csv`; таблиці в LaTeX генеруються скриптом `report/gen_tables.py`.

## Features

- **Array sorts**: Insertion, Quick, Merge, Heap, Bubble, Selection, Shell, Radix, Counting (single-threaded and multithreaded variants where applicable).
- **List sorts**: Quicksort, Counting sort, and Radix sort on a linked list of `Message` (MessageList).
- **Strategy pattern**: Array algorithms behind a common `SortStrategy<T>` interface with `SortContext<T>`.
- **Benchmarks**: Google Benchmark for array (Time arrays) and list (MessageList), plus strategy-based benchmarks with Google Test.

## Project layout

```
Sorting-Algorithms/
├── README.md
├── include/
│   └── sorting/
│       ├── strategy.hpp           # SortStrategy<T>, SortContext<T>
│       ├── array/                 # one header per algorithm
│       │   ├── insertion_sort.hpp
│       │   ├── quick_sort.hpp
│       │   ├── merge_sort.hpp
│       │   ├── heap_sort.hpp
│       │   ├── bubble_sort.hpp
│       │   ├── selection_sort.hpp
│       │   ├── shell_sort.hpp
│       │   ├── radix_sort.hpp
│       │   ├── counting_sort.hpp
│       │   ├── multithreaded_*.hpp
│       │   └── all_array_sorts.hpp
│       └── list/
│           ├── Message.h
│           ├── NodeList.h
│           └── message_list_sorts.hpp
├── common/
│   └── Time.hpp
├── apps/
│   ├── array_bench/     # Time-array benchmarks (Insertion, Quick, Merge, etc.)
│   ├── list_bench/      # MessageList benchmarks (qSortList, CountingSort, RadixSort)
│   ├── strategy_bench/   # Google Test + strategy-based benchmarks
│   └── sorting_charts/   # Qt6 app: graphs of sort time vs size (Uniform/Normal)
```

## Build

From the repo root:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Binaries will be in `build/` (e.g. `array_bench`, `list_bench`, `strategy_bench`, and optionally `sorting_charts`).

To build the **sorting_charts** Qt app (graphs of execution time vs array size for Uniform and Normal distributions), Qt6 with Widgets and Charts is required. Configure with Qt in `CMAKE_PREFIX_PATH`, for example on macOS with Homebrew:

```bash
cmake -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt@6)"
cmake --build build --target sorting_charts
./build/sorting_charts
```

If Qt6 is not found, the rest of the project still builds; only the `sorting_charts` target is omitted.

## Run

- **array_bench**: Run the executable; with Google Benchmark present it runs time-array benchmarks. Pass benchmark args as needed (e.g. `--benchmark_filter=Insertion`).
- **list_bench**: Same; benchmarks MessageList sorts. Without benchmark, interactive message list + qSort.
- **strategy_bench**: By default runs only unit tests (Google Test). Add `--run_benchmarks` to run strategy benchmarks after tests. Use GTest options (e.g. `--gtest_list_tests`, `--gtest_filter='SortingAlgorithms.*'`) and, when using `--run_benchmarks`, benchmark options as desired.
- **sorting_charts**: GUI app (Qt6). Choose int/double, click “Run benchmarks”; when finished, two tabs show line charts of execution time vs array size for Uniform and Normal distributions.

## Algorithm overview

| Name              | Type   | Time (avg)   | Time (worst) | Space   |
|-------------------|--------|-------------|--------------|---------|
| Insertion Sort    | array  | O(n²)       | O(n²)        | O(1)    |
| Quick Sort        | array  | O(n log n)  | O(n²)        | O(log n)|
| Merge Sort        | array  | O(n log n)  | O(n log n)   | O(n)    |
| Heap Sort         | array  | O(n log n)  | O(n log n)   | O(1)    |
| Bubble Sort       | array  | O(n²)       | O(n²)        | O(1)    |
| Selection Sort    | array  | O(n²)       | O(n²)        | O(1)    |
| Shell Sort        | array  | O(n^1.25)   | O(n²)        | O(1)    |
| Radix Sort        | array  | O(n·k)      | O(n·k)       | O(n+k)  |
| Counting Sort     | array  | O(n+k)      | O(n+k)       | O(k)    |
| List QuickSort    | list   | O(n log n)  | O(n²)        | O(log n)|
| List CountingSort| list   | O(n+k)      | O(n+k)       | O(k)    |
| List RadixSort    | list   | O(n·d)      | O(n·d)       | O(n)    |

*k: range of keys; d: number of digits.*

## Dependencies

- **Google Benchmark**: optional; used when `#include <benchmark/benchmark.h>` is available (array_bench, list_bench, strategy_bench).
- **Google Test**: fetched via CMake FetchContent (googletest) for unit tests in strategy_bench.
- **C++**: C++14 or later (C++17/20 for strategy_bench and modern toolchains).
- **Qt6** (optional): Widgets and Charts components for the `sorting_charts` app (e.g. `brew install qt@6` on macOS).

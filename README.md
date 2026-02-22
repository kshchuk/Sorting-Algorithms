# Sorting Algorithms

C++ implementations of sorting algorithms with benchmarks and tests.

## Features

- **Array sorts**: Insertion, Quick, Merge, Heap, Bubble, Selection, Shell, Radix, Counting (single-threaded and multithreaded variants where applicable).
- **List sorts**: Quicksort, Counting sort, and Radix sort on a linked list of `Message` (MessageList).
- **Strategy pattern**: Array algorithms behind a common `SortStrategy<T>` interface with `SortContext<T>`.
- **Benchmarks**: Google Benchmark for array (Time arrays) and list (MessageList), plus strategy-based benchmarks with doctest.

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
│   └── strategy_bench/   # doctest + strategy-based benchmarks
└── Sorting-Algorithms.sln
```

## Build

### Visual Studio

Open `Sorting-Algorithms.sln` at the repo root and build the solution. Ensure include paths point to `include/` and `common/` (the provided `.vcxproj` files set them relative to each app).

### CMake (optional, macOS/Linux)

From the repo root:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Binaries will be in `build/apps/array_bench`, `build/apps/list_bench`, `build/apps/strategy_bench` (or equivalent per generator).

## Run

- **array_bench**: Run the executable; with Google Benchmark present it runs time-array benchmarks. Pass benchmark args as needed (e.g. `--benchmark_filter=Insertion`).
- **list_bench**: Same; benchmarks MessageList sorts. Without benchmark, interactive message list + qSort.
- **strategy_bench**: Run tests (doctest) then strategy benchmarks. Use doctest options (e.g. `--list-test-cases`) and/or benchmark options as desired.

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
- **doctest**: vendored in `apps/strategy_bench/doctest.h` for unit tests.
- **C++**: C++14 or later (C++17/20 for strategy_bench and modern toolchains).

#include "sorting/array/all_array_sorts.hpp"
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <cstring>

#include "tests.hpp"
#include "benchmarks.hpp"

int main(int argc, char* argv[])
{
    bool run_benchmarks = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--run_benchmarks") == 0) {
            run_benchmarks = true;
            break;
        }
    }

    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    if (ret != 0) {
        return ret;
    }

    if (!run_benchmarks) {
        return 0;
    }

    REGISTER_BENCHMARK(int, sorting::InsertionSort);
    REGISTER_BENCHMARK(int, sorting::QuickSort);
    REGISTER_BENCHMARK(int, sorting::MergeSort);
    REGISTER_BENCHMARK(int, sorting::HeapSort);
    REGISTER_BENCHMARK(int, sorting::BubbleSort);
    REGISTER_BENCHMARK(int, sorting::SelectionSort);
    REGISTER_BENCHMARK(int, sorting::ShellSort);
    REGISTER_BENCHMARK(int, sorting::RadixSort);
    REGISTER_BENCHMARK(int, sorting::CountingSort);
    REGISTER_BENCHMARK(int, sorting::MultiThreadedQuickSort);
    REGISTER_BENCHMARK(int, sorting::MultiThreadedMergeSort);
    REGISTER_BENCHMARK(int, sorting::MultiThreadedHeapSort);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}

#include "MySorts.hpp"


#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include <benchmark/benchmark.h>

#include "tests.hpp"
#include "benchmarks.hpp"



int main(int argc, char* argv[])
{
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit()) {
        return res;
    }

    REGISTER_BENCHMARK(int, InsertionSort);
    REGISTER_BENCHMARK(int, QuickSort);
    REGISTER_BENCHMARK(int, MergeSort);
    REGISTER_BENCHMARK(int, HeapSort);
    REGISTER_BENCHMARK(int, BubbleSort);
    REGISTER_BENCHMARK(int, SelectionSort);
    REGISTER_BENCHMARK(int, ShellSort);
    REGISTER_BENCHMARK(int, RadixSort);
    REGISTER_BENCHMARK(int, CountingSort);
    REGISTER_BENCHMARK(int, MultiThreadedQuickSort);
    REGISTER_BENCHMARK(int, MultiThreadedMergeSort);
    REGISTER_BENCHMARK(int, MultiThreadedHeapSort);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}



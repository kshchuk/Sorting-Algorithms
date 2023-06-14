#pragma once
#include "MySorts.hpp"

#include <benchmark/benchmark.h> // https://github.com/google/benchmark
#include <vector>


// Generate a random array
std::vector<int> generateRandomArray(int n) {
    std::vector<int> arr(n);
    std::generate(arr.begin(), arr.end(), std::rand);
    return arr;
}

// Benchmark function for each sorting strategy
template <typename T>
void BM_Sort(benchmark::State& state, SortStrategy<T>* strategy) {
    for (auto _ : state) {
        state.PauseTiming();  // Pause timing while generating the array
        std::vector<int> arr = generateRandomArray(state.range(0));
        state.ResumeTiming();  // Resume timing for the sorting operation

        strategy->sort(arr.data(), arr.size());
    }
}

// Register the benchmark functions
#define REGISTER_BENCHMARK(T, STRATEGY) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY).c_str(), \
    [strategy = new STRATEGY<T>()](benchmark::State& state) { \
        for (auto _ : state) { \
            state.PauseTiming();  /* Pause timing while generating the array */ \
            std::vector<int> arr = generateRandomArray(state.range(0)); \
            state.ResumeTiming();  /* Resume timing for the sorting operation */ \
            strategy->sort(arr.data(), arr.size()); \
        } \
        delete strategy; \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int i = 10; i <= 10000; i *= 10) \
            b->Arg(i); \
    })->Unit(benchmark::kMillisecond)->UseRealTime();
#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include <benchmark/benchmark.h>
#include <vector>
#include <cstdlib>

inline std::vector<int> generateRandomArray(int n) {
    std::vector<int> arr(n);
    std::generate(arr.begin(), arr.end(), std::rand);
    return arr;
}

template <typename T>
void BM_Sort(benchmark::State& state, sorting::SortStrategy<T>* strategy) {
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> arr = generateRandomArray(state.range(0));
        state.ResumeTiming();

        strategy->sort(arr.data(), static_cast<int>(arr.size()));
    }
}

#define REGISTER_BENCHMARK(T, STRATEGY) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY).c_str(), \
    [strategy = new STRATEGY<T>()](benchmark::State& state) { \
        for (auto _ : state) { \
            state.PauseTiming(); \
            std::vector<int> arr = generateRandomArray(state.range(0)); \
            state.ResumeTiming(); \
            strategy->sort(arr.data(), static_cast<int>(arr.size())); \
        } \
        delete strategy; \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int i = 10; i <= 10000; i *= 10) \
            b->Arg(i); \
    })->Unit(benchmark::kMillisecond)->UseRealTime()

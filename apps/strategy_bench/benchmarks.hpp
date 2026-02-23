#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include "data_generators.hpp"
#include <benchmark/benchmark.h>
#include <vector>

template <typename T, typename GenFunc>
void runBenchmarkWithGenerator(benchmark::State& state, sorting::SortStrategy<T>* strategy, GenFunc gen) {
    for (auto _ : state) {
        state.PauseTiming();
        auto arr = gen(state.range(0));
        state.ResumeTiming();
        strategy->sort(arr.data(), static_cast<int>(arr.size()));
    }
}

#define REGISTER_BENCHMARK(T, STRATEGY) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY + "/Uniform").c_str(), \
    [strategy = new STRATEGY<T>()](benchmark::State& state) { \
        runBenchmarkWithGenerator(state, strategy, bench_data::generateUniformInt); \
        delete strategy; \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int i = 10; i <= 10000; i *= 10) b->Arg(i); \
    })->Unit(benchmark::kMillisecond)->UseRealTime()

#define REGISTER_BENCHMARK_DIST(T, STRATEGY, DistName, GenFunc) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY + "/" + DistName).c_str(), \
    [strategy = new STRATEGY<T>()](benchmark::State& state) { \
        for (auto _ : state) { \
            state.PauseTiming(); \
            auto arr = GenFunc(state.range(0)); \
            state.ResumeTiming(); \
            strategy->sort(arr.data(), static_cast<int>(arr.size())); \
        } \
        delete strategy; \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int i = 10; i <= 10000; i *= 10) b->Arg(i); \
    })->Unit(benchmark::kMillisecond)->UseRealTime()

/** Реєструє бенчмарки для трьох розподілів: Uniform, Normal, AsymptoticReverse */
#define REGISTER_BENCHMARK_ALL_DISTS(T, STRATEGY) \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Uniform", bench_data::generateUniformInt); \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Normal", bench_data::generateNormalInt); \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "AsymptoticReverse", bench_data::generateAsymptoticReverseSortedInt)

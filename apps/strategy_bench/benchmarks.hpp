#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include "data_generators.hpp"
#include <benchmark/benchmark.h>
#include <chrono>
#include <memory>
#include <vector>

constexpr std::chrono::seconds kBenchmarkTimeout{300};  // 5 min

template <typename T, typename GenFunc>
void runBenchmarkWithGenerator(benchmark::State& state, sorting::SortStrategy<T>* strategy, GenFunc gen) {
    auto deadline = std::chrono::steady_clock::now() + kBenchmarkTimeout;
    for (auto _ : state) {
        if (std::chrono::steady_clock::now() > deadline) break;
        state.PauseTiming();
        auto arr = gen(state.range(0));
        state.ResumeTiming();
        state.SetComplexityN(state.range(0));
        strategy->sort(arr.data(), static_cast<int>(arr.size()));
    }
}

/** Розміри масивів для бенчмарку (як у експерименті, макс 100000). */
constexpr int kBenchmarkSizes[] = { 10000, 20000, 50000, 100000 };

#define REGISTER_BENCHMARK(T, STRATEGY) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY + "/Uniform").c_str(), \
    [](benchmark::State& state) { \
        auto strategy = std::make_unique<STRATEGY<T>>(); \
        runBenchmarkWithGenerator(state, strategy.get(), bench_data::generateUniformInt); \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int n : kBenchmarkSizes) b->Arg(n); \
    })->Unit(benchmark::kMillisecond)->UseRealTime()->Complexity(benchmark::oAuto)

#define REGISTER_BENCHMARK_DIST(T, STRATEGY, DistName, GenFunc) \
    benchmark::RegisterBenchmark((std::string("BM_Sort/") + #STRATEGY + "/" + DistName).c_str(), \
    [](benchmark::State& state) { \
        auto strategy = std::make_unique<STRATEGY<T>>(); \
        auto deadline = std::chrono::steady_clock::now() + kBenchmarkTimeout; \
        for (auto _ : state) { \
            if (std::chrono::steady_clock::now() > deadline) break; \
            state.PauseTiming(); \
            auto arr = GenFunc(state.range(0)); \
            state.ResumeTiming(); \
            state.SetComplexityN(state.range(0)); \
            strategy->sort(arr.data(), static_cast<int>(arr.size())); \
        } \
    })->Apply([](benchmark::internal::Benchmark* b) { \
        for (int n : kBenchmarkSizes) b->Arg(n); \
    })->Unit(benchmark::kMillisecond)->UseRealTime()->Complexity(benchmark::oAuto)

/** Реєструє бенчмарки для чотирьох розподілів як у run_experiment: Worst, Uniform, Normal, Best */
#define REGISTER_BENCHMARK_ALL_DISTS(T, STRATEGY) \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Worst", bench_data::generateAsymptoticReverseSortedInt); \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Uniform", bench_data::generateUniformInt); \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Normal", bench_data::generateNormalInt); \
    REGISTER_BENCHMARK_DIST(T, STRATEGY, "Best", bench_data::generateAsymptoticSortedInt)

#pragma once

#include "memory_tracker.hpp"
#include "sorting/instrumented_type.hpp"
#include "sorting/array/all_array_sorts.hpp"
#include "data_generators.hpp"
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace experiment {

struct Sample {
    size_t V_bytes = 0;
    size_t K = 0;
    double T_ms = 0.0;
};

struct ExperimentResult {
    std::string algorithm;
    std::string condition;
    int n = 0;
    Sample sample;
};

inline const std::vector<int>& defaultSizes() {
    static const std::vector<int> sizes = {
        10000, 20000, 50000, 100000, 200000, 500000, 1000000
    };
    return sizes;
}

template <typename CountedT>
using GeneratorFn = std::function<std::vector<CountedT>(int)>;

template <typename CountedT>
std::vector<GeneratorFn<CountedT>> getConditionGenerators(const std::string& algorithm, bool isInt) {
    (void)algorithm;
    (void)isInt;
    if (isInt) {
        return {
            bench_data::generateAsymptoticReverseSortedCountedInt,
            bench_data::generateUniformCountedInt,
            bench_data::generateNormalCountedInt,
            bench_data::generateAsymptoticSortedCountedInt
        };
    } else {
        return {
            bench_data::generateAsymptoticReverseSortedCountedDouble,
            bench_data::generateUniformCountedDouble,
            bench_data::generateNormalCountedDouble,
            bench_data::generateAsymptoticSortedCountedDouble
        };
    }
}

template <>
inline std::vector<GeneratorFn<sorting::CountedInt>> getConditionGenerators<sorting::CountedInt>(
    const std::string& algorithm, bool /*isInt*/) {
    static const std::vector<std::string> mergeLike = {
        "MergeSort", "HeapSort", "MultiThreadedMergeSort", "MultiThreadedHeapSort"
    };
    bool mergeLikeOrder = false;
    for (const auto& s : mergeLike) {
        if (algorithm.find(s) != std::string::npos) { mergeLikeOrder = true; break; }
    }
    if (mergeLikeOrder) {
        return {
            bench_data::generateAsymptoticSortedCountedInt,
            bench_data::generateUniformCountedInt,
            bench_data::generateNormalCountedInt,
            bench_data::generateAsymptoticReverseSortedCountedInt
        };
    }
    return {
        bench_data::generateAsymptoticReverseSortedCountedInt,
        bench_data::generateUniformCountedInt,
        bench_data::generateNormalCountedInt,
        bench_data::generateAsymptoticSortedCountedInt
    };
}

template <>
inline std::vector<GeneratorFn<sorting::CountedDouble>> getConditionGenerators<sorting::CountedDouble>(
    const std::string& algorithm, bool /*isInt*/) {
    static const std::vector<std::string> mergeLike = {
        "MergeSort", "HeapSort", "MultiThreadedMergeSort", "MultiThreadedHeapSort"
    };
    bool mergeLikeOrder = false;
    for (const auto& s : mergeLike) {
        if (algorithm.find(s) != std::string::npos) { mergeLikeOrder = true; break; }
    }
    if (mergeLikeOrder) {
        return {
            bench_data::generateAsymptoticSortedCountedDouble,
            bench_data::generateUniformCountedDouble,
            bench_data::generateNormalCountedDouble,
            bench_data::generateAsymptoticReverseSortedCountedDouble
        };
    }
    return {
        bench_data::generateAsymptoticReverseSortedCountedDouble,
        bench_data::generateUniformCountedDouble,
        bench_data::generateNormalCountedDouble,
        bench_data::generateAsymptoticSortedCountedDouble
    };
}

inline std::vector<std::string> conditionNames() {
    return { "Worst", "Uniform", "Normal", "Best" };
}

constexpr std::chrono::seconds kExperimentTimeout{300};  // 5 min per (algo, condition, n)

template <typename CountedT>
Sample runOne(sorting::SortStrategy<CountedT>* strategy,
              GeneratorFn<CountedT> gen,
              int n,
              int numRuns) {
    Sample s;
    size_t sumK = 0;
    double sumT_ms = 0;
    size_t sumV = 0;
    auto deadline = std::chrono::steady_clock::now() + kExperimentTimeout;
    int completedRuns = 0;

    for (int run = 0; run < numRuns; ++run) {
        if (std::chrono::steady_clock::now() > deadline) break;
        std::vector<CountedT> arr = gen(n);
        experiment::MemoryTracker::get().reset();
        sorting::resetInstrumentation();

        auto t0 = std::chrono::steady_clock::now();
        strategy->sort(arr.data(), n);
        auto t1 = std::chrono::steady_clock::now();

        sumK += sorting::getTotalOperations();
        sumT_ms += 1e-6 * std::chrono::duration<double, std::nano>(t1 - t0).count();
        sumV += experiment::MemoryTracker::get().getPeakBytes();
        ++completedRuns;
    }

    s.K = completedRuns > 0 ? (sumK / static_cast<size_t>(completedRuns)) : 0;
    s.T_ms = completedRuns > 0 ? (sumT_ms / completedRuns) : 0;
    s.V_bytes = completedRuns > 0 ? (sumV / static_cast<size_t>(completedRuns)) : 0;
    return s;
}

template <typename CountedT>
int numRunsForCondition(size_t conditionIndex) {
    return (conditionIndex == 1 || conditionIndex == 2) ? 100 : 1;
}

// Run experiment for one algorithm (by index 0..13), one condition (0..3), one size.
template <typename CountedT>
Sample runSingle(int algoIndex, int conditionIndex, int n,
                 const std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<CountedT>>>>& strategies,
                 const std::vector<GeneratorFn<CountedT>>& generators) {
    if (algoIndex < 0 || algoIndex >= static_cast<int>(strategies.size())) return {};
    auto& strat = strategies[algoIndex].second;
    if (!strat) return {};
    int runs = numRunsForCondition<CountedT>(conditionIndex);
    return runOne(strat.get(), generators[conditionIndex], n, runs);
}

template <typename CountedT>
std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<CountedT>>>> makeStrategies();

template <>
inline std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<sorting::CountedInt>>>> makeStrategies<sorting::CountedInt>() {
    std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<sorting::CountedInt>>>> v;
    v.emplace_back("InsertionSort", std::make_unique<sorting::InsertionSort<sorting::CountedInt>>());
    v.emplace_back("QuickSort", std::make_unique<sorting::QuickSort<sorting::CountedInt>>());
    v.emplace_back("MergeSort", std::make_unique<sorting::MergeSort<sorting::CountedInt>>());
    v.emplace_back("HeapSort", std::make_unique<sorting::HeapSort<sorting::CountedInt>>());
    v.emplace_back("BubbleSort", std::make_unique<sorting::BubbleSort<sorting::CountedInt>>());
    v.emplace_back("SelectionSort", std::make_unique<sorting::SelectionSort<sorting::CountedInt>>());
    v.emplace_back("ShellSort", std::make_unique<sorting::ShellSort<sorting::CountedInt>>());
    v.emplace_back("RadixSort", std::make_unique<sorting::RadixSort<sorting::CountedInt>>());
    v.emplace_back("CountingSort", std::make_unique<sorting::CountingSort<sorting::CountedInt>>());
    v.emplace_back("MultiThreadedInsertionSort", std::make_unique<sorting::MultiThreadedInsertionSort<sorting::CountedInt>>());
    v.emplace_back("MultiThreadedQuickSort", std::make_unique<sorting::MultiThreadedQuickSort<sorting::CountedInt>>());
    v.emplace_back("MultiThreadedMergeSort", std::make_unique<sorting::MultiThreadedMergeSort<sorting::CountedInt>>());
    v.emplace_back("MultiThreadedHeapSort", std::make_unique<sorting::MultiThreadedHeapSort<sorting::CountedInt>>());
    v.emplace_back("MultiThreadedBubbleSort", std::make_unique<sorting::MultiThreadedBubbleSort<sorting::CountedInt>>());
    return v;
}

template <>
inline std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<sorting::CountedDouble>>>> makeStrategies<sorting::CountedDouble>() {
    std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<sorting::CountedDouble>>>> v;
    v.emplace_back("InsertionSort", std::make_unique<sorting::InsertionSort<sorting::CountedDouble>>());
    v.emplace_back("QuickSort", std::make_unique<sorting::QuickSort<sorting::CountedDouble>>());
    v.emplace_back("MergeSort", std::make_unique<sorting::MergeSort<sorting::CountedDouble>>());
    v.emplace_back("HeapSort", std::make_unique<sorting::HeapSort<sorting::CountedDouble>>());
    v.emplace_back("BubbleSort", std::make_unique<sorting::BubbleSort<sorting::CountedDouble>>());
    v.emplace_back("SelectionSort", std::make_unique<sorting::SelectionSort<sorting::CountedDouble>>());
    v.emplace_back("ShellSort", std::make_unique<sorting::ShellSort<sorting::CountedDouble>>());
    // RadixSort and CountingSort require integral types; skip for double
    v.emplace_back("MultiThreadedInsertionSort", std::make_unique<sorting::MultiThreadedInsertionSort<sorting::CountedDouble>>());
    v.emplace_back("MultiThreadedQuickSort", std::make_unique<sorting::MultiThreadedQuickSort<sorting::CountedDouble>>());
    v.emplace_back("MultiThreadedMergeSort", std::make_unique<sorting::MultiThreadedMergeSort<sorting::CountedDouble>>());
    v.emplace_back("MultiThreadedHeapSort", std::make_unique<sorting::MultiThreadedHeapSort<sorting::CountedDouble>>());
    v.emplace_back("MultiThreadedBubbleSort", std::make_unique<sorting::MultiThreadedBubbleSort<sorting::CountedDouble>>());
    return v;
}

template <typename CountedT>
std::vector<ExperimentResult> runAll(bool isInt, const std::vector<int>& sizes = defaultSizes(),
                                    bool showProgress = true) {
    std::vector<ExperimentResult> results;
    auto strategies = makeStrategies<CountedT>();
    auto condNames = conditionNames();

    const size_t totalAlgos = strategies.size();
    const size_t totalPerAlgo = sizes.size() * 4u;
    const size_t totalSteps = totalAlgos * totalPerAlgo;
    size_t step = 0;
    const char* typeLabel = isInt ? "int" : "double";

    for (size_t a = 0; a < strategies.size(); ++a) {
        const std::string& algoName = strategies[a].first;
        auto generators = getConditionGenerators<CountedT>(algoName, isInt);
        auto deadline = std::chrono::steady_clock::now() + kExperimentTimeout;

        for (int n : sizes) {
            if (std::chrono::steady_clock::now() > deadline) {
                if (showProgress) {
                    std::cerr << "[" << typeLabel << "] " << algoName << " timeout, skipping N>=" << n << "\n" << std::flush;
                }
                step += (sizes.size() - static_cast<size_t>(std::find(sizes.begin(), sizes.end(), n) - sizes.begin())) * 4u;
                break;
            }
            for (size_t c = 0; c < 4u; ++c) {
                if (std::chrono::steady_clock::now() > deadline) break;
                if (showProgress) {
                    std::cerr << "[" << typeLabel << "] " << (step + 1) << "/" << totalSteps
                              << " " << algoName << " N=" << n << " " << condNames[c] << " ... "
                              << std::flush;
                }
                Sample s = runSingle<CountedT>(static_cast<int>(a), static_cast<int>(c), n, strategies, generators);
                if (showProgress) {
                    std::cerr << " done\n" << std::flush;
                }
                ExperimentResult r;
                r.algorithm = algoName;
                r.condition = condNames[c];
                r.n = n;
                r.sample = s;
                results.push_back(r);
                ++step;
            }
        }
    }
    return results;
}

inline void printTableCSV(const std::vector<ExperimentResult>& results, std::ostream& out, const std::string& typeLabel) {
    out << "type,algorithm,condition,N,V_bytes,K,T_ms\n";
    for (const auto& r : results) {
        out << typeLabel << "," << r.algorithm << "," << r.condition << "," << r.n << ","
            << r.sample.V_bytes << "," << r.sample.K << "," << r.sample.T_ms << "\n";
    }
}

inline void printTableMarkdown(const std::vector<ExperimentResult>& results, std::ostream& out, const std::string& typeLabel) {
    out << "## Table for " << typeLabel << "\n\n";
    out << "| Algorithm | Condition | N | V (B) | K | T (ms) |\n|-----------|-----------|---|-------|---|--------|\n";
    for (const auto& r : results) {
        out << "| " << r.algorithm << " | " << r.condition << " | " << r.n << " | "
            << r.sample.V_bytes << " | " << r.sample.K << " | " << r.sample.T_ms << " |\n";
    }
}

inline void runAndPrint(bool intFirst = true, bool showProgress = true) {
    if (intFirst) {
        if (showProgress) std::cerr << "=== Experiment: int ===\n" << std::flush;
        auto resInt = runAll<sorting::CountedInt>(true, defaultSizes(), showProgress);
        std::cout << "--- Table for int ---\n";
        printTableCSV(resInt, std::cout, "int");
        std::cout << "\n";
        if (showProgress) std::cerr << "=== Experiment: double ===\n" << std::flush;
        auto resDouble = runAll<sorting::CountedDouble>(false, defaultSizes(), showProgress);
        std::cout << "--- Table for double ---\n";
        printTableCSV(resDouble, std::cout, "double");
        if (showProgress) std::cerr << "=== Done ===\n" << std::flush;
    } else {
        if (showProgress) std::cerr << "=== Experiment: double ===\n" << std::flush;
        auto resDouble = runAll<sorting::CountedDouble>(false, defaultSizes(), showProgress);
        printTableCSV(resDouble, std::cout, "double");
        if (showProgress) std::cerr << "=== Experiment: int ===\n" << std::flush;
        auto resInt = runAll<sorting::CountedInt>(true, defaultSizes(), showProgress);
        printTableCSV(resInt, std::cout, "int");
        if (showProgress) std::cerr << "=== Done ===\n" << std::flush;
    }
}

}  // namespace experiment

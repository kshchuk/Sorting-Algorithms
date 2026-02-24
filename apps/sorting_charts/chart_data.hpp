#pragma once

#include "sorting/array/all_array_sorts.hpp"
#include "data_generators.hpp"
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace chart_data {

/** distribution name -> algorithm name -> [(n, time_ms), ...] */
using ChartResults = std::map<std::string, std::map<std::string, std::vector<std::pair<int, double>>>>;

/** Optional progress: (currentStep, totalSteps, description) */
using ProgressFn = std::function<void(int, int, const std::string&)>;

inline std::vector<int> defaultSizes() {
    return { 1000, 5000, 10000, 50000, 100000 };
}

template <typename T>
ChartResults runImpl(
    const std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<T>>>>& strategies,
    const std::function<std::vector<T>(int)>& genUniform,
    const std::function<std::vector<T>(int)>& genNormal,
    ProgressFn progress = nullptr)
{
    ChartResults results;
    const auto sizes = defaultSizes();
    const int numRuns = 3;
    const std::vector<std::pair<std::string, std::function<std::vector<T>(int)>>> dists = {
        { "Uniform", genUniform },
        { "Normal", genNormal }
    };
    const int totalSteps = static_cast<int>(dists.size() * strategies.size() * sizes.size());
    int step = 0;

    for (const auto& distPair : dists) {
        const std::string& distName = distPair.first;
        const auto& gen = distPair.second;
        for (const auto& algoPair : strategies) {
            const std::string& algoName = algoPair.first;
            const auto& strategy = algoPair.second;
            auto& series = results[distName][algoName];
            series.clear();
            for (int n : sizes) {
                double sumMs = 0;
                for (int r = 0; r < numRuns; ++r) {
                    std::vector<T> arr = gen(n);
                    auto t0 = std::chrono::steady_clock::now();
                    strategy->sort(arr.data(), n);
                    auto t1 = std::chrono::steady_clock::now();
                    sumMs += 1e-6 * std::chrono::duration<double, std::nano>(t1 - t0).count();
                }
                series.emplace_back(n, sumMs / numRuns);
                ++step;
                if (progress) {
                    progress(step, totalSteps, algoName + " " + distName + " N=" + std::to_string(n));
                }
            }
        }
    }
    return results;
}

inline ChartResults runInt(ProgressFn progress = nullptr) {
    std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<int>>>> strategies;
    strategies.emplace_back("InsertionSort", std::make_unique<sorting::InsertionSort<int>>());
    strategies.emplace_back("QuickSort", std::make_unique<sorting::QuickSort<int>>());
    strategies.emplace_back("MergeSort", std::make_unique<sorting::MergeSort<int>>());
    strategies.emplace_back("HeapSort", std::make_unique<sorting::HeapSort<int>>());
    strategies.emplace_back("BubbleSort", std::make_unique<sorting::BubbleSort<int>>());
    strategies.emplace_back("SelectionSort", std::make_unique<sorting::SelectionSort<int>>());
    strategies.emplace_back("ShellSort", std::make_unique<sorting::ShellSort<int>>());
    strategies.emplace_back("RadixSort", std::make_unique<sorting::RadixSort<int>>());
    strategies.emplace_back("CountingSort", std::make_unique<sorting::CountingSort<int>>());
    strategies.emplace_back("MultiThreadedInsertionSort", std::make_unique<sorting::MultiThreadedInsertionSort<int>>());
    strategies.emplace_back("MultiThreadedQuickSort", std::make_unique<sorting::MultiThreadedQuickSort<int>>());
    strategies.emplace_back("MultiThreadedMergeSort", std::make_unique<sorting::MultiThreadedMergeSort<int>>());
    strategies.emplace_back("MultiThreadedHeapSort", std::make_unique<sorting::MultiThreadedHeapSort<int>>());
    strategies.emplace_back("MultiThreadedBubbleSort", std::make_unique<sorting::MultiThreadedBubbleSort<int>>());
    return runImpl<int>(strategies, bench_data::generateUniformInt, bench_data::generateNormalInt, progress);
}

inline ChartResults runDouble(ProgressFn progress = nullptr) {
    std::vector<std::pair<std::string, std::unique_ptr<sorting::SortStrategy<double>>>> strategies;
    strategies.emplace_back("InsertionSort", std::make_unique<sorting::InsertionSort<double>>());
    strategies.emplace_back("QuickSort", std::make_unique<sorting::QuickSort<double>>());
    strategies.emplace_back("MergeSort", std::make_unique<sorting::MergeSort<double>>());
    strategies.emplace_back("HeapSort", std::make_unique<sorting::HeapSort<double>>());
    strategies.emplace_back("BubbleSort", std::make_unique<sorting::BubbleSort<double>>());
    strategies.emplace_back("SelectionSort", std::make_unique<sorting::SelectionSort<double>>());
    strategies.emplace_back("ShellSort", std::make_unique<sorting::ShellSort<double>>());
    strategies.emplace_back("MultiThreadedInsertionSort", std::make_unique<sorting::MultiThreadedInsertionSort<double>>());
    strategies.emplace_back("MultiThreadedQuickSort", std::make_unique<sorting::MultiThreadedQuickSort<double>>());
    strategies.emplace_back("MultiThreadedMergeSort", std::make_unique<sorting::MultiThreadedMergeSort<double>>());
    strategies.emplace_back("MultiThreadedHeapSort", std::make_unique<sorting::MultiThreadedHeapSort<double>>());
    strategies.emplace_back("MultiThreadedBubbleSort", std::make_unique<sorting::MultiThreadedBubbleSort<double>>());
    return runImpl<double>(strategies,
        [](int n) { return bench_data::generateUniformDouble(n); },
        [](int n) { return bench_data::generateNormalDouble(n); },
        progress);
}

inline ChartResults run(bool useInt, ProgressFn progress = nullptr) {
    return useInt ? runInt(progress) : runDouble(progress);
}

}  // namespace chart_data

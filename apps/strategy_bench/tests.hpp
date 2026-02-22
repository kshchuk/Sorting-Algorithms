#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <cstdlib>

namespace {

const std::vector<int> kTestSizes = { 0, 1, 5, 100, 1000, 2000 };

template <typename Strategy>
void runSortTestsForStrategy() {
    Strategy s;
    std::srand(42);
    for (int n : kTestSizes) {
        std::vector<int> arr(n);
        if (n > 0) {
            for (int i = 0; i < n; ++i)
                arr[i] = n - 1 - i;
        }
        std::vector<int> expected = arr;
        std::sort(expected.begin(), expected.end());
        if (n > 0) {
            s.sort(arr.data(), n);
        }
        EXPECT_EQ(arr, expected) << "Reverse-ordered array of size " << n;

        if (n > 0) {
            for (int i = 0; i < n; ++i)
                arr[i] = std::rand() % (2 * n + 1);
            expected = arr;
            std::sort(expected.begin(), expected.end());
            s.sort(arr.data(), n);
            EXPECT_EQ(arr, expected) << "Random array of size " << n;
        }
    }
}

}  // namespace

TEST(SortingAlgorithms, InsertionSort) {
    runSortTestsForStrategy<sorting::InsertionSort<int>>();
}

TEST(SortingAlgorithms, QuickSort) {
    runSortTestsForStrategy<sorting::QuickSort<int>>();
}

TEST(SortingAlgorithms, MergeSort) {
    runSortTestsForStrategy<sorting::MergeSort<int>>();
}

TEST(SortingAlgorithms, HeapSort) {
    runSortTestsForStrategy<sorting::HeapSort<int>>();
}

TEST(SortingAlgorithms, BubbleSort) {
    runSortTestsForStrategy<sorting::BubbleSort<int>>();
}

TEST(SortingAlgorithms, SelectionSort) {
    runSortTestsForStrategy<sorting::SelectionSort<int>>();
}

TEST(SortingAlgorithms, ShellSort) {
    runSortTestsForStrategy<sorting::ShellSort<int>>();
}

TEST(SortingAlgorithms, RadixSort) {
    runSortTestsForStrategy<sorting::RadixSort<int>>();
}

TEST(SortingAlgorithms, CountingSort) {
    runSortTestsForStrategy<sorting::CountingSort<int>>();
}

TEST(SortingAlgorithms, MultiThreadedQuickSort) {
    runSortTestsForStrategy<sorting::MultiThreadedQuickSort<int>>();
}

TEST(SortingAlgorithms, MultiThreadedMergeSort) {
    runSortTestsForStrategy<sorting::MultiThreadedMergeSort<int>>();
}

TEST(SortingAlgorithms, MultiThreadedHeapSort) {
    runSortTestsForStrategy<sorting::MultiThreadedHeapSort<int>>();
}

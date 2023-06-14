#include "sorting_algorithms.hpp"
#include <gtest/gtest.h> // https://github.com/google/googletest

#include <algorithm>

// Test case for Insertion Sort algorithm
TEST(SortingAlgorithmsTest, InsertionSortTest) {
    int arr[] = { 5, 4, 3, 2, 1 };
    int expected[] = { 1, 2, 3, 4, 5 };
    SortingAlgorithms<int>::InsertionSort(arr, 5);
    ASSERT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

// Test case for Quick Sort algorithm
TEST(SortingAlgorithmsTest, QuickSortTest) {
    int arr[] = { 5, 4, 3, 2, 1 };
    int expected[] = { 1, 2, 3, 4, 5 };
    SortingAlgorithms<int>::QuickSort(arr, 0, 4);
    ASSERT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

// Test case for Merge Sort algorithm
TEST(SortingAlgorithmsTest, MergeSortTest) {
    int arr[] = { 5, 4, 3, 2, 1 };
    int expected[] = { 1, 2, 3, 4, 5 };
    SortingAlgorithms<int>::MergeSort(arr, new int[5], 5);
    ASSERT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

// Test case for Heap Sort algorithm
TEST(SortingAlgorithmsTest, HeapSortTest) {
    int arr[] = { 5, 4, 3, 2, 1 };
    int expected[] = { 1, 2, 3, 4, 5 };
    SortingAlgorithms<int>::HeapSort(arr, 5);
    ASSERT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include <gtest/gtest.h>
#include <algorithm>

TEST(SortingAlgorithms, InsertionSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::InsertionSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, QuickSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::QuickSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, MergeSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::MergeSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, HeapSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::HeapSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, BubbleSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::BubbleSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, SelectionSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::SelectionSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, ShellSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::ShellSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, RadixSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::RadixSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, CountingSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::CountingSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, MultiThreadedQuickSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::MultiThreadedQuickSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, MultiThreadedMergeSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::MultiThreadedMergeSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

TEST(SortingAlgorithms, MultiThreadedHeapSort) {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };
    sorting::MultiThreadedHeapSort<int> s;
    s.sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));
    s.sort(reverse_sorted_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));
    s.sort(duplicate_arr, 5);
    EXPECT_TRUE(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
}

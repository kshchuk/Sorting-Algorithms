#pragma once
#include "sorting/array/all_array_sorts.hpp"
#include "doctest.h"

TEST_CASE("Testing sorting algorithms") {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };

    SUBCASE("Testing InsertionSort") {
        sorting::InsertionSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing QuickSort") {
        sorting::QuickSort<int> qs;
        qs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        qs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        qs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MergeSort") {
        sorting::MergeSort<int> ms;
        ms.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        ms.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        ms.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing HeapSort") {
        sorting::HeapSort<int> hs;
        hs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        hs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        hs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing BubbleSort") {
        sorting::BubbleSort<int> bs;
        bs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        bs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        bs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing SelectionSort") {
        sorting::SelectionSort<int> ss;
        ss.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        ss.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        ss.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing ShellSort") {
        sorting::ShellSort<int> shs;
        shs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        shs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        shs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing RadixSort") {
        sorting::RadixSort<int> rs;
        rs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        rs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        rs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing CountingSort") {
        sorting::CountingSort<int> cs;
        cs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        cs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        cs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadedQuickSort") {
        sorting::MultiThreadedQuickSort<int> mtqs;
        mtqs.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        mtqs.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        mtqs.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadedMergeSort") {
        sorting::MultiThreadedMergeSort<int> mtms;
        mtms.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        mtms.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        mtms.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadedHeapSort") {
        sorting::MultiThreadedHeapSort<int> mths;
        mths.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        mths.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        mths.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }
}

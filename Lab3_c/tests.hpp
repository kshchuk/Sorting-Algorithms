#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MySorts.hpp"

TEST_CASE("Testing sorting algorithms") {
    int arr[5] = { 5, 4, 3, 2, 1 };
    int sorted_arr[5] = { 1, 2, 3, 4, 5 };
    int reverse_sorted_arr[5] = { 5, 4, 3, 2, 1 };
    int duplicate_arr[5] = { 5, 5, 3, 3, 1 };
    int duplicate_sorted_arr[5] = { 1, 3, 3, 5, 5 };

    SUBCASE("Testing InsertionSort") {
        InsertionSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing QuickSort") {
        QuickSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }


    SUBCASE("Testing MergeSort") {
        MergeSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }


    SUBCASE("Testing HeapSort") {
        HeapSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing BubbleSort") {
        BubbleSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing SelectionSort") {
        SelectionSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }


    SUBCASE("Testing ShellSort") {
        ShellSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing RadixSort") {
        RadixSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing CountingSort") {
        CountingSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }


    SUBCASE("Testing MultiThreadedInsertionSort") {
        MultiThreadedInsertionSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadedQuickSort") {
        MultiThreadedQuickSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }


    SUBCASE("Testing MultiThreadedMergeSort") {
        MultiThreadedMergeSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadedHeapSort") {
        MultiThreadedHeapSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }

    SUBCASE("Testing MultiThreadeBubbleSort") {
        MultiThreadeBubbleSort<int> insertionSort;
        insertionSort.sort(arr, 5);
        CHECK(std::equal(std::begin(arr), std::end(arr), std::begin(sorted_arr)));

        insertionSort.sort(reverse_sorted_arr, 5);
        CHECK(std::equal(std::begin(reverse_sorted_arr), std::end(reverse_sorted_arr), std::begin(sorted_arr)));

        insertionSort.sort(duplicate_arr, 5);
        CHECK(std::equal(std::begin(duplicate_arr), std::end(duplicate_arr), std::begin(duplicate_sorted_arr)));
    }
}

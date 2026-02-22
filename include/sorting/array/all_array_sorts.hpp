#pragma once

#include "insertion_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "shell_sort.hpp"
#include "radix_sort.hpp"
#include "counting_sort.hpp"
#include "multithreaded_insertion_sort.hpp"
#include "multithreaded_quick_sort.hpp"
#include "multithreaded_merge_sort.hpp"
#include "multithreaded_heap_sort.hpp"
#include "multithreaded_bubble_sort.hpp"

#include <cstdint>

namespace sorting {

// All strategy classes are available in namespace sorting (e.g. sorting::InsertionSort<T>).

}  // namespace sorting

/*
 * Free-function API for array_bench (backward compatibility with Lab3_a style).
 * Sorts arr[0..size-1] or arr[start..end] (inclusive).
 */
template <typename T>
inline void InsertionSort(T* arr, int64_t size) {
    sorting::InsertionSort<T>().sort(arr, static_cast<int>(size));
}

template <typename T>
inline void QuickSort(T* arr, int64_t start, int64_t end) {
    if (start < 0 || end < start) return;
    int size = static_cast<int>(end - start + 1);
    sorting::QuickSort<T>().sort(arr + start, size);
}

template <typename T>
inline void MergeSort(T* arr1, T* /* arr2 */, int64_t size) {
    sorting::MergeSort<T>().sort(arr1, static_cast<int>(size));
}

template <typename T>
inline void MixedSort(T* arr1, T* arr2, int64_t size) {
    MergeSort<T>(arr1, arr2, size);
}

#pragma once

#include "../strategy.hpp"
#include <thread>
#include <algorithm>

namespace sorting {

template <typename T>
class MultiThreadedQuickSort : public SortStrategy<T> {
    static constexpr int kMinSizeForThreads = 5000;

public:
    void sort(T* arr, int size) override {
        quickSort(arr, 0, size - 1);
    }

private:
    void quickSort(T* arr, int low, int high) {
        if (low >= high) return;
        int pi = partition(arr, low, high);
        int size = high - low + 1;
        if (size <= kMinSizeForThreads) {
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
            return;
        }
        std::thread leftThread(&MultiThreadedQuickSort::quickSort, this, arr, low, pi - 1);
        std::thread rightThread(&MultiThreadedQuickSort::quickSort, this, arr, pi + 1, high);
        leftThread.join();
        rightThread.join();
    }

    int partition(T* arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

}  // namespace sorting

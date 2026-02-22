#pragma once

#include "../strategy.hpp"
#include <thread>
#include <mutex>
#include <algorithm>

namespace sorting {

template <typename T>
class MultiThreadedQuickSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        quickSort(arr, 0, size - 1);
    }

private:
    void quickSort(T* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            std::thread leftThread(&MultiThreadedQuickSort::quickSort, this, arr, low, pi - 1);
            std::thread rightThread(&MultiThreadedQuickSort::quickSort, this, arr, pi + 1, high);
            leftThread.join();
            rightThread.join();
        }
    }

    int partition(T* arr, int low, int high) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                mtx.lock();
                i++;
                std::swap(arr[i], arr[j]);
                mtx.unlock();
            }
        }
        mtx.lock();
        std::swap(arr[i + 1], arr[high]);
        mtx.unlock();
        return (i + 1);
    }
    std::mutex mtx;
};

}  // namespace sorting

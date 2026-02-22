#pragma once

#include "../strategy.hpp"
#include <thread>
#include <algorithm>

namespace sorting {

template <typename T>
class MultiThreadedHeapSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        std::thread first(&MultiThreadedHeapSort::heapify, this, arr, size, size / 2 - 1);
        std::thread second(&MultiThreadedHeapSort::heapify, this, arr, size, size / 2 - 1);
        first.join();
        second.join();

        for (int i = size - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            std::thread t(&MultiThreadedHeapSort::heapify, this, arr, i, 0);
            t.join();
        }
    }

private:
    void heapify(T* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

}  // namespace sorting

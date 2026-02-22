#pragma once

#include "../strategy.hpp"
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

namespace sorting {

/**
 * @class MultiThreadedBubbleSort
 * @brief Class for multithreaded bubble sort strategy.
 */
template <typename T>
class MultiThreadedBubbleSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        std::vector<std::thread> threads;
        for (int i = 0; i < size - 1; i++) {
            threads.push_back(std::thread(&MultiThreadedBubbleSort::bubbleSortPass, this, arr, size, i));
        }
        for (auto& th : threads) th.join();
    }

private:
    void bubbleSortPass(T* arr, int size, int i) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::lock_guard<std::mutex> lock(mtx);
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::mutex mtx;
};

}  // namespace sorting

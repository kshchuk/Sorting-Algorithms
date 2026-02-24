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
    static constexpr int kMaxThreads = 64;

public:
    void sort(T* arr, int size) override {
        const int numPasses = size - 1;
        if (numPasses <= 0) return;
        if (numPasses <= kMaxThreads) {
            std::vector<std::thread> threads;
            threads.reserve(static_cast<size_t>(numPasses));
            for (int i = 0; i < numPasses; i++) {
                threads.emplace_back(&MultiThreadedBubbleSort::bubbleSortPass, this, arr, size, i);
            }
            for (auto& th : threads) th.join();
        } else {
            for (int i = 0; i < numPasses; i++) {
                bubbleSortPass(arr, size, i);
            }
        }
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

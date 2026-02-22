#pragma once

#include "../strategy.hpp"
#include <thread>
#include <mutex>
#include <vector>

namespace sorting {

template <typename T>
class MultiThreadedInsertionSort : public SortStrategy<T> {
    std::mutex mtx;
public:
    void sort(T* arr, int size) override {
        T t;
        int64_t i;
        std::vector<std::thread> threads;
        for (int64_t j = 1; j < size; j++) {
            threads.push_back(std::thread([&, j] {
                t = arr[j];
                i = j - 1;
                mtx.lock();
                while ((i >= 0) && (arr[i] > t)) {
                    arr[i + 1] = arr[i];
                    i--;
                }
                arr[i + 1] = t;
                mtx.unlock();
            }));
        }
        for (auto& th : threads) {
            th.join();
        }
    }
};

}  // namespace sorting

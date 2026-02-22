#pragma once

#include "../strategy.hpp"
#include <algorithm>

namespace sorting {

template <typename T>
class BubbleSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

}  // namespace sorting

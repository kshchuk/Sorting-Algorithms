#pragma once

#include "../strategy.hpp"
#include <algorithm>

namespace sorting {

template <typename T>
class SelectionSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        int min_idx;
        for (int i = 0; i < size - 1; i++) {
            min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            std::swap(arr[min_idx], arr[i]);
        }
    }
};

}  // namespace sorting

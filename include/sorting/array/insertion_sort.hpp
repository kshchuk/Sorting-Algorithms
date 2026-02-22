#pragma once

#include "../strategy.hpp"
#include <algorithm>

namespace sorting {

template <typename T>
class InsertionSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        T t;
        int64_t i;
        for (int64_t j = 1; j < size; j++) {
            t = arr[j];
            i = j - 1;
            while ((i >= 0) && (arr[i] > t)) {
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = t;
        }
    }
};

}  // namespace sorting

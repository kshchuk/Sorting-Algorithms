#pragma once

#include "../strategy.hpp"
#include <algorithm>

namespace sorting {

template <typename T>
class RadixSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        T max_val = *std::max_element(arr, arr + size);
        for (int exp = 1; max_val / exp > 0; exp *= 10) {
            countSort(arr, size, exp);
        }
    }

private:
    void countSort(T* arr, int size, int exp) {
        T* output = new T[size];
        int count[10] = { 0 };

        for (int i = 0; i < size; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < size; i++) {
            arr[i] = output[i];
        }
        delete[] output;
    }
};

}  // namespace sorting

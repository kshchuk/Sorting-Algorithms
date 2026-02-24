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
    static int digit(T x, int exp) {
        int d = (x / exp) % 10;
        return d < 0 ? d + 10 : d;
    }

    void countSort(T* arr, int size, int exp) {
        T* output = new T[size];
        int count[10] = { 0 };

        for (int i = 0; i < size; i++) {
            count[digit(arr[i], exp)]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            int d = digit(arr[i], exp);
            output[count[d] - 1] = arr[i];
            count[d]--;
        }

        for (int i = 0; i < size; i++) {
            arr[i] = output[i];
        }
        delete[] output;
    }
};

}  // namespace sorting

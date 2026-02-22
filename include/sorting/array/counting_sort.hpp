#pragma once

#include "../strategy.hpp"
#include <algorithm>
#include <vector>

namespace sorting {

template <typename T>
class CountingSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        T max_val = *std::max_element(arr, arr + size);
        T min_val = *std::min_element(arr, arr + size);
        int range = max_val - min_val + 1;

        std::vector<int> count(range), output(size);
        for (int i = 0; i < size; i++) {
            count[arr[i] - min_val]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            output[count[arr[i] - min_val] - 1] = arr[i];
            count[arr[i] - min_val]--;
        }

        for (int i = 0; i < size; i++) {
            arr[i] = output[i];
        }
    }
};

}  // namespace sorting

#pragma once

#include "../strategy.hpp"

namespace sorting {

template <typename T>
class ShellSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i += 1) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }
};

}  // namespace sorting

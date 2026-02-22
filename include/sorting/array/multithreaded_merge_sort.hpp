#pragma once

#include "../strategy.hpp"
#include <thread>

namespace sorting {

template <typename T>
class MultiThreadedMergeSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        mergeSort(arr, 0, size - 1);
    }

private:
    void mergeSort(T* arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            std::thread left_sort([=] { mergeSort(arr, left, mid); });

            if (right - left > 10000) {
                std::thread right_sort([=] { mergeSort(arr, mid + 1, right); });
                right_sort.join();
            } else {
                mergeSort(arr, mid + 1, right);
            }

            left_sort.join();

            merge(arr, left, mid, right);
        }
    }

    void merge(T* arr, int left, int mid, int right) {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        T* L = new T[n1];
        T* R = new T[n2];
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }
};

}  // namespace sorting

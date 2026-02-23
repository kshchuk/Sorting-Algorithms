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
    static constexpr int kMinSizeForThreads = 5000;

    void mergeSort(T* arr, int left, int right) {
        if (left >= right) return;
        int size = right - left + 1;
        int mid = left + (right - left) / 2;

        if (size <= kMinSizeForThreads) {
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
            return;
        }

        std::thread left_sort([=] { mergeSort(arr, left, mid); });
        std::thread right_sort([=] { mergeSort(arr, mid + 1, right); });
        left_sort.join();
        right_sort.join();
        merge(arr, left, mid, right);
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

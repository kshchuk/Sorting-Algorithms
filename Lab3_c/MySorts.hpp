
#include <iostream>

//============================================================== 2. Insertion sort ===================================================================//

template<typename T>
void InsertionSort(T* arr, int64_t size)
{
    T t;
    int64_t i;
    for (int64_t j = 1; j < size; j++)
    {
        t = arr[j];
        i = j - 1;
        while ((i >= 0) && (arr[i] < t))
        {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = t;
    }
}


// ============================================== 8. Hoare partition scheme, median-of-three pivot ===================================================//

template<typename T> int64_t SortPartition(T*, int64_t, int64_t);

template<typename T>
void QuickSort(T* arr, int64_t start, int64_t end)
{
    if (start >= 0 && end >= 0 && start < end)
    {
        int64_t part = SortPartition(arr, start, end);
        QuickSort(arr, start, part);
        QuickSort(arr, part + 1, end);
    }
    else
        return;
}

template<typename T>
int64_t SortPartition(T* arr, int64_t start, int64_t end)
{
    // median-of-three pivot
    int64_t mid = (start + end) / 2;
    if (arr[mid] > arr[start])
        std::swap(arr[start], arr[mid]);
    if (arr[end] > arr[start])
        std::swap(arr[start], arr[end]);
    if (arr[mid] > arr[end])
        std::swap(arr[mid], arr[end]);
    T pivot = arr[end];

    int64_t left = start - 1;
    int64_t right = end + 1;

    while (true)
    {
        do
        {
            left++;
        } while (arr[left] > pivot);
        do
        {
            right--;
        } while (arr[right] < pivot);

        if (left >= right)
            return right;
        std::swap(arr[left], arr[right]);
    }
}


// ========================================================= 1.top-down, two arrays =================================================================== //

template<typename T> void Merge(T*, T*, int64_t, int64_t, int64_t);
template<typename T> void SplitMerge(T*, T*, int64_t, int64_t);
template<typename T> void CopyArray(T*, T*, int64_t, int64_t);

template<typename T>
void MergeSort(T* arr1, T* arr2, int64_t size)
{
    CopyArray(arr1, arr2, 0, size);
    SplitMerge(arr2, arr1, 0, size);
}

template<typename T>
void Merge(T* arr1, T* arr2, int64_t start, int64_t mid, int64_t end)
{
    int64_t i = start;
    int64_t j = mid;
    for (int64_t k = start; k < end; k++)
    {
        if (i < mid && (j >= end || arr1[i] <= arr1[j]))
        {
            arr2[k] = arr1[i];
            i++;
        }
        else {
            arr2[k] = arr1[j];
            j++;
        }
    }
}

template<typename T>
void SplitMerge(T* arr2, T* arr1, int64_t start, int64_t end)
{
    if (end - start <= 1)
        return;
    int64_t mid = (start + end) / 2;
    SplitMerge(arr1, arr2, start, mid);
    SplitMerge(arr1, arr2, mid, end);
    Merge(arr1, arr2, start, mid, end);
}

template<typename T>
void CopyArray(T* arr1, T* arr2, int64_t start, int64_t end)
{
    for (int64_t k = start; k < end; k++)
        arr2[k] = arr1[k];
}


// ===================================================================Mixed sort========================================================================//
// base - MergeSort
// 10-element - InsertionSort

template<typename T>
void MergeMixedSort(T* arr1, T* arr2, int64_t start, int64_t end)
{
    T t;
    int64_t i;
    for (int64_t j = start; j < end; j++)
    {
        t = arr2[j];
        i = j - 1;
        while ((i >= start) && (arr2[i] < t))
        {
            arr2[i + 1] = arr2[i];
            i--;
        }
        arr2[i + 1] = t;
    }
}

template<typename T>
void SplitMergeMixedSort(T* arr2, T* arr1, int64_t start, int64_t end)
{
    if (end - start <= 1)
        return;
    else if (end - start < 10)
    {
        MergeMixedSort(arr1, arr2, start, end);
        return;
    }
    SplitMerge(arr1, arr2, start + 10, end);
    MergeMixedSort(arr1, arr2, start, end);
}

template<typename T>
void MixedSort(T* arr1, T* arr2, int64_t size)
{
    CopyArray(arr1, arr2, 0, size);
    SplitMergeMixedSort(arr2, arr1, 0, size);
}
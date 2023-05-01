
/**
 * @file sorting_algorithms.hpp
 * @brief This file contains three sorting algorithms implemented in C++
 * @details These sorting algorithms are templated and can be used to sort arrays of any data type. Doxygen comments are included for documenting the code.
 */


#include <iostream>
#include <thread>


 /**
  * @brief A class for sorting algorithms.
  * @tparam T Data type of the array elements.
  */
template<typename T>
class SortingAlgorithms {
public:
    /**
     * @brief Insertion Sort algorithm.
     * @param arr Pointer to the array to be sorted.
     * @param size Size of the array.
     */
    static void InsertionSort(T* arr, int64_t size);

    /**
     * @brief Quick Sort algorithm.
     * @param arr Pointer to the array to be sorted.
     * @param start Start index of the array.
     * @param end End index of the array.
     */
    static void QuickSort(T* arr, int64_t start, int64_t end);

    /**
     * @brief Merge Sort algorithm.
     * @param arr1 Pointer to the first array to be sorted.
     * @param arr2 Pointer to the second array used for temporary storage during the sorting process.
     * @param size Size of the array.
     */
    static void MergeSort(T* arr1, T* arr2, int64_t size);

     /**
     * @brief Heap Sort algorithm.
     * @param arr Pointer to the array to be sorted.
     * @param n size of the array.
     */
    static void HeapSort(T arr[], int n);

    static void QuickSortMT(T* arr, int size, int max_depth) {
        QuickSortAuxMT(arr, size, max_depth, 1);
    }

    static void MergeSortMT(T arr[], int size, int max_depth);


private:
    /**
     * @brief Get the pivot element for Quick Sort algorithm.
     * @param arr Pointer to the array.
     * @param start Start index of the array.
     * @param end End index of the array.
     * @return The pivot element.
     */
    static T GetPivot(T* arr, int64_t start, int64_t end);

    /**
     * @brief Helper function for Merge Sort algorithm.
     * @param arr1 Pointer to the first array.
     * @param arr2 Pointer to the second array used for temporary storage during the sorting process.
     * @param start Start index of the array.
     * @param mid Mid index of the array.
     * @param end End index of the array.
     */
    static void Merge(T* arr1, T* arr2, int64_t start, int64_t mid, int64_t end);

    /**
     * @brief Helper function for Merge Sort algorithm.
     * @param arr2 Pointer to the second array.
     * @param arr1 Pointer to the first array used for temporary storage during the sorting process.
     * @param start Start index of the array.
     * @param end End index of the array.
     */
    static void SplitMerge(T* arr2, T* arr1, int64_t start, int64_t end);

    /**
     * @brief Helper function for Merge Sort algorithm.
     * @param arr1 Pointer to the first array.
     * @param arr2 Pointer to the second array.
     * @param start Start index of the array.
     * @param end End index of the array.
     */
    static void CopyArray(T* arr1, T* arr2, int64_t start, int64_t end);

    /**
     * @brief Helper function for Quick Sort algorithm.
     * @param arr Pointer to the array.
     * @param start Start index of the array.
     * @param end End index of the array.
     * @return The partition index.
     */
    static int64_t SortPartition(T* arr, int64_t start, int64_t end);


    /**
     * @brief Helper function for Heap Sort algorithm.
     * @param arr Pointer to the array.
     * @param n size of the array.
     * @param start Start index of the array.
     */
    static void Heapify(T arr[], int n, int i);

    static void QuickSortAuxMT(T* arr, int size, int maxDepth, int curDepth);

    static void MergeSortAuxMT(T* arr, T* temp, int size, int cur_depth, int max_depth);

    static void Merge(T a[], int sizeA, T b[], int sizeB, T c[]);

    static void FillTheRest(T* dst, int dstIndex, T* src, int srcIndex, int size);
};


template<typename T>
void SortingAlgorithms<T>::InsertionSort(T* arr, int64_t size)
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

template<typename T>
void SortingAlgorithms<T>::QuickSort(T* arr, int64_t start, int64_t end)
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

template<typename T> T SortingAlgorithms<T>::GetPivot(T* arr, int64_t start, int64_t end) {
    // median-of-three pivot
    int64_t mid = (start + end) / 2;
    if (arr[mid] > arr[start])
        std::swap(arr[start], arr[mid]);
    if (arr[end] > arr[start])
        std::swap(arr[start], arr[end]);
    if (arr[mid] > arr[end])
        std::swap(arr[mid], arr[end]);
    return arr[end];
}


template<typename T>
int64_t SortingAlgorithms<T>::SortPartition(T* arr, int64_t start, int64_t end)
{
    T pivot = GetPivot(arr, start, end);

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

template<typename T>
void SortingAlgorithms<T>::MergeSort(T* arr1, T* arr2, int64_t size)
{
    CopyArray(arr1, arr2, 0, size);
    SplitMerge(arr2, arr1, 0, size);
}

template<typename T>
void SortingAlgorithms<T>::Merge(T* arr1, T* arr2, int64_t start, int64_t mid, int64_t end)
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
void SortingAlgorithms<T>::SplitMerge(T* arr2, T* arr1, int64_t start, int64_t end)
{
    if (end - start <= 1)
        return;
    int64_t mid = (start + end) / 2;
    SplitMerge(arr1, arr2, start, mid);
    SplitMerge(arr1, arr2, mid, end);
    Merge(arr1, arr2, start, mid, end);
}

template<typename T>
void SortingAlgorithms<T>::CopyArray(T* arr1, T* arr2, int64_t start, int64_t end)
{
    for (int64_t k = start; k < end; k++)
        arr2[k] = arr1[k];
}

template<typename T>
void SortingAlgorithms<T>::HeapSort(T arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {

        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


template <typename T>
void SortingAlgorithms<T>::Heapify(T arr[], int n, int i)
{
    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        Heapify(arr, n, largest);
    }
}

template<class T>
void SortingAlgorithms<T>::QuickSortAuxMT(T* arr, int size, int maxDepth, int curDepth) {
    int p, left = 1, right = size - 1;
    if (size < 2)
        return;
    //partition
    std::swap(arr[0], arr[size / 2]);
    p = arr[0];
    while (left <= right) {
        while (right >= left && arr[right] >= p)
            right--;
        while (left <= right && arr[left] < p)
            left++;
        if (left < right)
            std::swap(arr[left++], arr[right--]);
    }
    std::swap(arr[0], arr[right]);
    //end of partition
    if (curDepth <= maxDepth) {
        std::thread t([&]() { QuickSortAuxMT(arr, right, maxDepth, curDepth + 1); });
        std::thread t2([&]() { QuickSortAuxMT(arr + right + 1, size - right - 1, maxDepth, curDepth + 1); });
        //wait for threads to finish
        t.join();
        t2.join();
    }
    else {
        QuickSortAuxMT(arr, right, maxDepth, curDepth + 1);
        QuickSortAuxMT(arr + right + 1, size - right - 1, maxDepth, curDepth + 1);
    }
}


template<typename T>
void SortingAlgorithms<T>::MergeSortMT(T arr[], int size, int max_depth) {
    T* temp = new T[size];
    //in case of allocation error will throw bad_alloc
    MergeSortAuxMT(arr, temp, size, 1, max_depth);
    delete[] temp;
}

template<typename T>
void SortingAlgorithms<T>::MergeSortAuxMT(T* arr, T* temp, int size, int cur_depth, int max_depth) {
    if (size < 2) {
        return;
    }
    int left = size / 2;
    if (cur_depth <= max_depth) {
        std::thread t([&]() { MergeSortAuxMT(arr, temp, left, cur_depth + 1, max_depth); });
        std::thread t1([&]() { MergeSortAuxMT((arr + left), temp + left, (size - left), cur_depth + 1, max_depth); });
        //wait for threads to finish
        t.join();
        t1.join();
    }
    else {
        MergeSortAuxMT(arr, temp, left, cur_depth + 1, max_depth);
        MergeSortAuxMT(arr + left, temp + left, (size - left), cur_depth + 1, max_depth);
    }
    Merge(arr, left, arr + left, size - left, temp);
    memcpy(arr, temp, size * sizeof(T));
}

template<typename T>
void SortingAlgorithms<T>::Merge(T a[], int sizeA, T b[], int sizeB, T c[]) {
    int ia = 0, ib = 0, ic = 0;
    while (ia < sizeA && ib < sizeB) {
        if (a[ia] <= b[ib]) {
            c[ic] = a[ia];
            ia++;
        }
        else {
            c[ic] = b[ib];
            ib++;
        }
        ic++;
    }
    fillTheRest(c, ic, a, ia, sizeA);
    fillTheRest(c, ic, b, ib, sizeB);
}


template<typename T>
void SortingAlgorithms<T>::FillTheRest(T* dst, int dstIndex, T* src, int srcIndex, int size) {
    while (srcIndex < size) {
        dst[dstIndex] = src[srcIndex];
        dstIndex++;
        srcIndex++;
    }
}
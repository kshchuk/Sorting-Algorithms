#include <iostream>

#include <cstring>
#include <algorithm>
#include <vector>

#include <thread>
#include <mutex>


/**
 * @class SortStrategy
 * @brief Abstract base class for sorting strategies.
 */
template <typename T>
class SortStrategy {
public:
    virtual void sort(T* arr, int size) = 0;
};

/**
 * @class InsertionSort
 * @brief Class for insertion sort strategy.
 */
template <typename T>
class InsertionSort : public SortStrategy<T> {
public:
    /**
     * @brief Sorts the array using insertion sort.
     * @param arr The array to be sorted.
     * @param size The size of the array.
     */
    void sort(T* arr, int size) override {
        T t;
        int64_t i;
        for (int64_t j = 1; j < size; j++) {
            t = arr[j];
            i = j - 1;
            while ((i >= 0) && (arr[i] < t)) {
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = t;
        }
    }
};

/**
 * @class QuickSort
 * @brief Class for quick sort strategy.
 */
template <typename T>
class QuickSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        quickSort(arr, 0, size - 1);
    }

private:
    void quickSort(T* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(T* arr, int low, int high) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
};

/**
 * @class MergeSort
 * @brief Class for merge sort strategy.
 */
template <typename T>
class MergeSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        mergeSort(arr, 0, size - 1);
    }

private:
    void mergeSort(T* arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void merge(T* arr, int left, int mid, int right) {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        T* L = new T[n1], *R = new T[n2];
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
            }
            else {
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

        delete[] L, R;
    }
};

/**
 * @class HeapSort
 * @brief Class for heap sort strategy.
 */
template <typename T>
class HeapSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(arr, size, i);
        for (int i = size - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

private:
    void heapify(T* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};


/**
 * @class BubbleSort
 * @brief Class for bubble sort strategy.
 */
template <typename T>
class BubbleSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

/**
 * @class SelectionSort
 * @brief Class for selection sort strategy.
 */
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

/**
 * @class ShellSort
 * @brief Class for shell sort strategy.
 */
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


/**
 * @class RadixSort
 * @brief Class for radix sort strategy.
 */
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

/**
 * @class CountingSort
 * @brief Class for counting sort strategy.
 */
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

/*------------------------------------------------------------MULTITHREADING-------------------------------------------------------------------------------*/

/**
 * @class MultiThreadedInsertionSort
 * @brief Class for multithreaded insertion sort strategy.
 */
template <typename T>
class MultiThreadedInsertionSort : public SortStrategy<T> {
    std::mutex mtx;
public:
    /**
     * @brief Sorts the array using multithreaded insertion sort.
     * @param arr The array to be sorted.
     * @param size The size of the array.
     */
    void sort(T* arr, int size) override {
        T t;
        int64_t i;
        std::vector<std::thread> threads;
        for (int64_t j = 1; j < size; j++) {
            threads.push_back(std::thread([&, j] {
                t = arr[j];
                i = j - 1;
                mtx.lock();
                while ((i >= 0) && (arr[i] < t)) {
                    arr[i + 1] = arr[i];
                    i--;
                }
                arr[i + 1] = t;
                mtx.unlock();
                }));
        }
        for (auto& th : threads) {
            th.join();
        }
    }
};

/**
 * @class MultiThreadedQuickSort
 * @brief Class for multithreaded quick sort strategy.
 */
template <typename T>
class MultiThreadedQuickSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        quickSort(arr, 0, size - 1);
    }

private:
    void quickSort(T* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            std::thread leftThread(&MultiThreadedQuickSort::quickSort, this, arr, low, pi - 1);
            std::thread rightThread(&MultiThreadedQuickSort::quickSort, this, arr, pi + 1, high);
            leftThread.join();
            rightThread.join();
        }
    }

    int partition(T* arr, int low, int high) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                mtx.lock();
                i++;
                std::swap(arr[i], arr[j]);
                mtx.unlock();
            }
        }
        mtx.lock();
        std::swap(arr[i + 1], arr[high]);
        mtx.unlock();
        return (i + 1);
    }
    std::mutex mtx;
};


/**
 * @class MultiThreadedMergeSort
 * @brief Class for multithreaded merge sort strategy.
 */
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

            // If the size of the array is large enough, sort the right half in a new thread.
            if (right - left > 10000) {
                std::thread right_sort([=] { mergeSort(arr, mid + 1, right); });
                right_sort.join();
            }
            else {
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
        T* L = new T[n1], * R = new T[n2];
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
            }
            else {
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

        delete[] L, R;
    }
};


/**
 * @class MultiThreadedHeapSort
 * @brief Class for multithreaded heap sort strategy.
 */
template <typename T>
class MultiThreadedHeapSort : public SortStrategy<T> {
public:
    void sort(T* arr, int size) override {
        std::thread first(&MultiThreadedHeapSort::heapify, this, arr, size, size / 2 - 1);
        std::thread second(&MultiThreadedHeapSort::heapify, this, arr, size, size / 2 - 1);
        first.join();
        second.join();

        for (int i = size - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            std::thread t(&MultiThreadedHeapSort::heapify, this, arr, i, 0);
            t.join();
        }
    }

private:
    void heapify(T* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};


/**
 * @class MultiThreadeBubbleSort
 * @brief Class for bubble sort strategy.
 */
template <typename T>
class MultiThreadeBubbleSort : public SortStrategy<T> {
public:
    /**
     * @brief Sorts the array using bubble sort in a multithreaded manner.
     * @param arr The array to be sorted.
     * @param size The size of the array.
     */
    void sort(T* arr, int size) override {
        std::vector<std::thread> threads;
        for (int i = 0; i < size - 1; i++) {
            threads.push_back(std::thread(&MultiThreadeBubbleSort::bubbleSortPass, this, arr, size, i));
        }
        for (auto& th : threads) th.join();
    }

private:
    /**
     * @brief Performs a single pass of bubble sort.
     * @param arr The array to be sorted.
     * @param size The size of the array.
     * @param i The index of the pass.
     */
    void bubbleSortPass(T* arr, int size, int i) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::lock_guard<std::mutex> lock(mtx);
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::mutex mtx;
};



/**
 * @class SortContext
 * @brief Context class for sorting.
 */
template <typename T>
class SortContext {
private:
    SortStrategy<T>* strategy;
public:
    /**
     * @brief Constructor for SortContext.
     * @param strategy The sorting strategy to be used.
     */
    SortContext(SortStrategy<T>* strategy) : strategy(strategy) {}

    /**
     * @brief Sets the sorting strategy.
     * @param strategy The sorting strategy to be used.
     */
    void set_strategy(SortStrategy<T>* strategy) {
        this->strategy = strategy;
    }

    /**
     * @brief Sorts the array using the current strategy.
     * @param arr The array to be sorted.
     * @param size The size of the array.
     */
    void sort(T* arr, int size) {
        strategy->sort(arr, size);
    }
};




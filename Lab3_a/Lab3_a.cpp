
#include <iostream>



// 14. Дата і час, за спаданням

struct Time
{
    size_t year, month, day, hour, minute, second;
};

bool operator == (Time d1, Time d2)
{
    return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day) &&
        (d2.hour = d2.hour) && (d2.minute == d2.minute) && (d1.second == d1.second);
}

bool operator != (Time d1, Time d2)
{
    return !(d1 == d2);
}

bool operator < (Time d1, Time d2)
{
    if (d1.year < d2.year)
        return true;
    else if (d1.year == d2.year)
        if (d1.month < d2.month)
            return true;
        else if (d1.month == d2.month)
            if (d1.day < d2.day)
                return true;
            else if (d1.day == d2.day)
                if (d1.hour < d2.hour)
                    return true;
                else if (d1.hour == d2.hour)
                    if (d1.minute < d2.minute)
                        return true;
                    else if (d1.minute == d2.minute)
                        if (d1.second < d2.second)
                            return true;
                        else return false;
    return false;
}

bool operator > (Time d1, Time d2)
{
    return !(d1 < d2) && (d1 != d2);
}

bool operator <= (Time d1, Time d2)
{
    return (d1 < d2 || d1 == d2);
}

bool operator >= (Time d1, Time d2)
{
    return (d1 > d2 || d1 == d2);
}

Time operator - (Time d1, Time d2)
{
    Time t;
    if (d1.second - d2.second < 0) {
        d1.second += 60;
        d2.minute += 1;
    }
    t.second = d1.second - d2.second;
    if (d1.minute - d2.minute < 0) {
        d1.minute += 60;
        d2.hour += 1;
    }
    t.minute = d1.minute - d2.minute;
    if (d1.hour - d2.hour < 0) {
        d1.hour += 24;
        d2.day += 1;
    }
    t.hour = d1.hour - d2.hour;
    if (d1.day - d2.day < 0) {
        d1.day += 30;
        d2.month += 1;
    }
    t.day = d1.day - d2.day;
    if (d1.month - d2.month < 0) {
        d1.month += 12;
        d2.year += 1;
    }
    t.month = d1.month - d2.month;
    t.year = d1.year - d2.year;

    return t;
}


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

#if __has_include(<benchmark/benchmark.h>)
// =================================================================== BENCHMARKS ======================================================================//

#pragma comment ( lib, "Shlwapi.lib" )
#include <benchmark/benchmark.h>
#include <random>

void CreateArray(Time* t, int64_t size)
{
    for (int64_t i = 0; i < size; i++)
    {
        t[i].year = 2020 + rand() % 2;
        t[i].month = 6 + rand() % 3;
        t[i].day = 17 + rand() % 4;
        t[i].hour = 14 + rand() % 5;
        t[i].minute = 45 + rand() % 6;
        t[i].second = 25 + rand() % 7;
    }
}

static void InsertionSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)+1];
    CreateArray(t, state.range(0));
    for (auto _ : state) 
    {
        InsertionSort(t, state.range(0));
    }
    //delete[] t;
}


BENCHMARK(InsertionSort_BM)->RangeMultiplier(10)->Range(10, 100000)->Iterations(1);
//BENCHMARK(InsertionSort_BM)->Arg(1000000)->Iterations(1);

static void QuickSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)+1];
    CreateArray(t, state.range(0));
    for (auto _ : state) {
        QuickSort(t, 0, state.range(0));
    }
    //delete[] t;
}

BENCHMARK(QuickSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//BENCHMARK(QuickSort_BM)->Arg(100)->Iterations(1);

static void MergeSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    Time* b = new Time[state.range(0)];
    for (auto _ : state) {
        MergeSort(t, b, state.range(0));
    }
    //delete[] t, b;
}

BENCHMARK(MergeSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//BENCHMARK(MergeSort_BM)->Arg(100000000)->Iterations(1);

static void MixedSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    Time* b = new Time[state.range(0)];
    for (auto _ : state) {
        MergeSort(t, b, state.range(0));
    }
    //delete[] t, b;
}

BENCHMARK(MixedSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//BENCHMARK(MixedSort_BM)->Arg(100000000)->Iterations(1);

static void LibrarySort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    for (auto _ : state) {
        std::sort(t, t + state.range(0));
    }
    //delete[] t;
}

BENCHMARK(LibrarySort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//BENCHMARK(LibrarySort_BM)->Arg(100000000)->Iterations(1);

BENCHMARK_MAIN();

#else

//InsertionSort_BM / 10 / iterations:1             4900 ns        0.000 ns            1
//InsertionSort_BM / 100 / iterations : 1          9500 ns        0.000 ns            1
//InsertionSort_BM / 1000 / iterations : 1       443300 ns        0.000 ns            1
//InsertionSort_BM / 10000 / iterations : 1    39841100 ns     31250000 ns            1
//InsertionSort_BM / 100000 / iterations : 1 3833677800 ns   3828125000 ns            1
// 
//QuickSort_BM / 10 / iterations : 1               3900 ns        0.000 ns            1
//QuickSort_BM / 100 / iterations : 1             17100 ns        0.000 ns            1
//QuickSort_BM / 1000 / iterations : 1           159000 ns        0.000 ns            1
//QuickSort_BM / 10000 / iterations : 1         1784400 ns        0.000 ns            1
//QuickSort_BM / 100000 / iterations : 1       20723900 ns     15625000 ns            1
//QuickSort_BM / 1000000 / iterations : 1     226555900 ns    218750000 ns            1
//QuickSort_BM / 10000000 / iterations : 1   2371790100 ns   2359375000 ns            1
// 
//MergeSort_BM / 10 / iterations : 1               4700 ns        0.000 ns            1
//MergeSort_BM / 100 / iterations : 1             11500 ns        0.000 ns            1
//MergeSort_BM / 1000 / iterations : 1           128100 ns        0.000 ns            1
//MergeSort_BM / 10000 / iterations : 1         1492300 ns        0.000 ns            1
//MergeSort_BM / 100000 / iterations : 1       18710100 ns     15625000 ns            1
//MergeSort_BM / 1000000 / iterations : 1     196004500 ns    203125000 ns            1
//MergeSort_BM / 10000000 / iterations : 1   2261760600 ns   2234375000 ns            1
// 
//MixedSort_BM / 10 / iterations : 1               3300 ns        0.000 ns            1
//MixedSort_BM / 100 / iterations : 1             11700 ns        0.000 ns            1
//MixedSort_BM / 1000 / iterations : 1           135800 ns        0.000 ns            1
//MixedSort_BM / 10000 / iterations : 1         1493800 ns        0.000 ns            1
//MixedSort_BM / 100000 / iterations : 1       17355800 ns     31250000 ns            1
//MixedSort_BM / 1000000 / iterations : 1     202565700 ns    203125000 ns            1
//MixedSort_BM / 10000000 / iterations : 1   2254905700 ns   2265625000 ns            1
// 
//LibrarySort_BM / 10 / iterations : 1             2100 ns        0.000 ns            1
//LibrarySort_BM / 100 / iterations : 1           11200 ns        0.000 ns            1
//LibrarySort_BM / 1000 / iterations : 1         119900 ns        0.000 ns            1
//LibrarySort_BM / 10000 / iterations : 1       1331400 ns        0.000 ns            1
//LibrarySort_BM / 100000 / iterations : 1     13667700 ns     15625000 ns            1
//LibrarySort_BM / 1000000 / iterations : 1   122408000 ns    109375000 ns            1
//LibrarySort_BM / 10000000 / iterations : 1 1180332700 ns   1187500000 ns            1

int main()
{
    Time t1[] = { {2000, 12, 24, 5, 56, 34}, {2005, 12, 24, 3, 56, 76}, {2000, 11, 24, 5, 56, 34}, {2001, 32, 43, 5, 56, 34}, {2000, 1, 4, 5, 56, 34} };
    Time t2[5];

    //InsertionSort(t1, 5);
    //QuickSort(t1, 0, 5);
    MergeSort(t1, t2, 5);
    // my
    MixedSort(t1, t2, 5);
    for (int i = 0; i < 5; i++)
        std::cout << t2[i].year << ' ' << t2[i].month << ' ' << t2[i].day << ' ' << t2[i].hour << ' ' << t2[i].minute << ' ' << t2[i].second << std::endl;

}

#endif

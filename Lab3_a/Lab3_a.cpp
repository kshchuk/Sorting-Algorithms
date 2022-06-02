
#include <iostream>



// 14. Дата і час, за спаданням

#include "Time.hpp"
#include "MySorts.hpp"



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

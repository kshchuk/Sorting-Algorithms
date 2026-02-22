
#include <iostream>
#include <algorithm>

#include "Time.hpp"
#include "sorting/array/all_array_sorts.hpp"

#if __has_include(<benchmark/benchmark.h>)
#pragma comment(lib, "Shlwapi.lib")
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
}

BENCHMARK(InsertionSort_BM)->RangeMultiplier(10)->Range(10, 100000)->Iterations(1);

static void QuickSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)+1];
    CreateArray(t, state.range(0));
    for (auto _ : state) {
        QuickSort(t, 0, state.range(0));
    }
}

BENCHMARK(QuickSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);

static void MergeSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    Time* b = new Time[state.range(0)];
    for (auto _ : state) {
        MergeSort(t, b, state.range(0));
    }
}

BENCHMARK(MergeSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);

static void MixedSort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    Time* b = new Time[state.range(0)];
    for (auto _ : state) {
        MergeSort(t, b, state.range(0));
    }
}

BENCHMARK(MixedSort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);

static void LibrarySort_BM(benchmark::State& state)
{
    Time* t = new Time[state.range(0)];
    CreateArray(t, state.range(0));
    for (auto _ : state) {
        std::sort(t, t + state.range(0));
    }
}

BENCHMARK(LibrarySort_BM)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);

BENCHMARK_MAIN();

#else

int main()
{
    Time t1[] = { {2000, 12, 24, 5, 56, 34}, {2005, 12, 24, 3, 56, 76}, {2000, 11, 24, 5, 56, 34}, {2001, 12, 24, 5, 56, 34}, {2000, 1, 4, 5, 56, 34} };
    Time t2[5];

    MergeSort(t1, t2, 5);
    MixedSort(t1, t2, 5);
    for (int i = 0; i < 5; i++)
        std::cout << t1[i].year << ' ' << t1[i].month << ' ' << t1[i].day << ' ' << t1[i].hour << ' ' << t1[i].minute << ' ' << t1[i].second << std::endl;
}

#endif

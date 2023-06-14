//#if __has_include(<benchmark/benchmark.h>)
//#pragma comment ( lib, "Shlwapi.lib" )
//#include <benchmark/benchmark.h>                // https://github.com/google/benchmark
//
//#include <random>
//#include "sorting_algorithms.hpp"
//
//static void BM_HeapSort(benchmark::State& state)
//{
//    std::random_device rd;
//    std::mt19937 mersenne(rd());
//
//    int* arr = randomArr(state.range(0));
//    
//    for (auto _ : state) {
//        heapSort(arr, state.range(0));
//    }
//    delete[] arr;
//}
//
//
//static void BM_QuickSort_MT(benchmark::State& state)
//{
//    std::random_device rd;
//    std::mt19937 mersenne(rd());
//
//    int threadsNum = std::thread::hardware_concurrency();
//    int* arr = randomArr(state.range(0));
//
//    for (auto _ : state) {
//        QuickSortMT(arr, state.range(0), threadsNum);
//    }
//    delete[] arr;
//
//}
//
//static void BM_MergeSort_MT(benchmark::State& state)
//{
//    std::random_device rd;
//    std::mt19937 mersenne(rd());
//
//    int* arr = randomArr(state.range(0));
//    int threadsNum = std::thread::hardware_concurrency();
//
//    for (auto _ : state) {
//        mergeSortMT(arr, state.range(0), threadsNum);
//    }
//    delete[] arr;
//
//}
//
//#include "MySorts.hpp"
//
//
//int comparator(const void* p1, const void* p2) {
//    int l = *(const int*)p1;
//    int r = *(const int*)p2;
//    return (l - r);
//}
//
//static void QuickSort_BM(benchmark::State& state)
//{
//    int* arr = randomArr(state.range(0));
//
//    for (auto _ : state) {
//        qsort(arr, state.range(0), sizeof(int), comparator);
//    }
//    delete[] arr;
//}
//
//
//static void MergeSort_BM(benchmark::State& state)
//{
//    int* arr1 = randomArr(state.range(0));
//    int* arr2 = new int[state.range(0)];
//
//    for (auto _ : state) {
//        MergeSort(arr1, arr2, state.range(0));
//    }
//    delete[] arr1, arr2;
//}
//
//static void LibrarySort_BM(benchmark::State& state)
//{
//    int* arr1 = randomArr(state.range(0));
//
//    for (auto _ : state) {
//        std::sort(arr1, arr1 + state.range(0));
//    }
//    delete[] arr1;
//}
//
//
//
//
//BENCHMARK(BM_HeapSort)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//BENCHMARK(BM_QuickSort_MT)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 100000000)->Iterations(1);
//BENCHMARK(QuickSort_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 100000000)->Iterations(1);
//BENCHMARK(BM_MergeSort_MT)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 100000000)->Iterations(1);
//BENCHMARK(MergeSort_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 100000000)->Iterations(1);
//BENCHMARK(LibrarySort_BM)->Unit(benchmark::kMicrosecond)->RangeMultiplier(10)->Range(10, 10000000)->Iterations(1);
//
//
//
//
//BENCHMARK_MAIN();
//
//#endif
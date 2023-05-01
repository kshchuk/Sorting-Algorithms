//#include "sort"
//
//#include <random>
//
//int* randomArr(size_t size) {
//    std::random_device rd;
//    std::mt19937 mersenne(rd());
//
//    int* arr = new int[size];
//    for (size_t i = 0; i < size; i++)
//        arr[i] = mersenne() % size;
//    return arr;
//}
//
//



//#else



//2022 - 06 - 04T00:17 : 53 + 03 : 00
//Running D : \Univercity\1_kurs\OOP_Basic\Sort_lab3\Lab3_a\Release\Lab3_c.exe
//Run on(8 X 1996 MHz CPU s)
//CPU Caches :
//L1 Data 32 KiB(x8)
//L1 Instruction 32 KiB(x8)
//L2 Unified 512 KiB(x8)
//L3 Unified 4096 KiB(x2)
//-------------------------------------------------------------------------------- -
//Benchmark                                       Time             CPU   Iterations
//-------------------------------------------------------------------------------- -
//BM_HeapSort / 10 / iterations:1                  3.60 us        0.000 us            1
//BM_HeapSort / 100 / iterations : 1                 7.00 us        0.000 us            1
//BM_HeapSort / 1000 / iterations : 1                48.6 us        0.000 us            1
//BM_HeapSort / 10000 / iterations : 1                655 us        0.000 us            1
//BM_HeapSort / 100000 / iterations : 1              8619 us        15625 us            1
//BM_HeapSort / 1000000 / iterations : 1           179820 us       187500 us            1
//BM_HeapSort / 10000000 / iterations : 1         5265745 us      5250000 us            1
// 
//BM_QuickSort_MT / 10 / iterations : 1             12140 us        0.000 us            1
//BM_QuickSort_MT / 100 / iterations : 1            36722 us        0.000 us            1
//BM_QuickSort_MT / 1000 / iterations : 1          209866 us        0.000 us            1
//BM_QuickSort_MT / 10000 / iterations : 1         348655 us        0.000 us            1
//BM_QuickSort_MT / 100000 / iterations : 1        403510 us        0.000 us            1
//BM_QuickSort_MT / 1000000 / iterations : 1       465294 us        0.000 us            1
//BM_QuickSort_MT / 10000000 / iterations : 1      674920 us        15625 us            1
//BM_QuickSort_MT / 100000000 / iterations : 1    2483763 us       375000 us            1
// 
//QuickSort_BM / 10 / iterations : 1                 3.60 us        0.000 us            1
//QuickSort_BM / 100 / iterations : 1                10.2 us        0.000 us            1
//QuickSort_BM / 1000 / iterations : 1               91.8 us        0.000 us            1
//QuickSort_BM / 10000 / iterations : 1              1101 us        0.000 us            1
//QuickSort_BM / 100000 / iterations : 1            13382 us        0.000 us            1
//QuickSort_BM / 1000000 / iterations : 1          162448 us       156250 us            1
//QuickSort_BM / 10000000 / iterations : 1        1837425 us      1843750 us            1
//QuickSort_BM / 100000000 / iterations : 1      20667486 us     20640625 us            1
// 
//BM_MergeSort_MT / 10 / iterations : 1             14536 us        0.000 us            1
//BM_MergeSort_MT / 100 / iterations : 1           137083 us        0.000 us            1
//BM_MergeSort_MT / 1000 / iterations : 1          468615 us        0.000 us            1
//BM_MergeSort_MT / 10000 / iterations : 1         484256 us        0.000 us            1
//BM_MergeSort_MT / 100000 / iterations : 1        495767 us        0.000 us            1
//BM_MergeSort_MT / 1000000 / iterations : 1       518373 us        15625 us            1
//BM_MergeSort_MT / 10000000 / iterations : 1      791031 us        62500 us            1
//BM_MergeSort_MT / 100000000 / iterations : 1    3303826 us       562500 us            1
// 
//MergeSort_BM / 10 / iterations : 1                 3.20 us        0.000 us            1
//MergeSort_BM / 100 / iterations : 1                7.70 us        0.000 us            1
//MergeSort_BM / 1000 / iterations : 1               67.3 us        0.000 us            1
//MergeSort_BM / 10000 / iterations : 1               791 us        0.000 us            1
//MergeSort_BM / 100000 / iterations : 1             9430 us        15625 us            1
//MergeSort_BM / 1000000 / iterations : 1          114235 us       109375 us            1
//MergeSort_BM / 10000000 / iterations : 1        1286299 us      1281250 us            1
//MergeSort_BM / 100000000 / iterations : 1      14546065 us     14484375 us            1
// 
//LibrarySort_BM / 10 / iterations : 1               5.10 us        0.000 us            1
//LibrarySort_BM / 100 / iterations : 1              5.80 us        0.000 us            1
//LibrarySort_BM / 1000 / iterations : 1             35.4 us        0.000 us            1
//LibrarySort_BM / 10000 / iterations : 1             836 us        0.000 us            1
//LibrarySort_BM / 100000 / iterations : 1           5537 us        0.000 us            1
//LibrarySort_BM / 1000000 / iterations : 1         70601 us        62500 us            1
//LibrarySort_BM / 10000000 / iterations : 1       816895 us       828125 us            1

#include <iostream>
#include "gtest/gtest.h"


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//#endif


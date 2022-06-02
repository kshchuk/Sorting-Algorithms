
#if __has_include(<benchmark/benchmark.h>)
#pragma comment ( lib, "Shlwapi.lib" )
#include <benchmark/benchmark.h>                // https://github.com/google/benchmark
#endif
#include <random>
#include <cstdlib>
#include "MySorts.hpp"

std::string str("0123456789ABCDEFGHIJK.,.effrg3g33g3.3g3,r.g,/22f2f2f77372%$@&!@#$%^&*()hhfjfdjfjdu8ududjjhGYGYFJFDJIJilhlhudhudjhjhegeydyuegdgejdgeyjgdjygEJhgdyegdyuetduyegfFGUFIGYKGJGJFJFJGFHDGEJHDGEHKDGJEGFKJEGHGhjegy3t6t6!@#$%^&*()_!@#$%^&*()_++\\?><<dhgigegkegfkgkegkfgekgfkeLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

std::random_device rd;
std::mt19937 generator(rd());


std::string random_text(int r)
{
    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, r);    // assumes 32 < number of characters in str         
}

Time* randomTime(int r)
{
    Time* time = new Time();
    time->year = r % 10 + 2020;
    time->month = r % 13;
    time->day = r % 32;
    time->hour = r % 25;
    time->minute = r % 61;
    time->second = r % 60;
    return time;
}


MessageList* lis = new MessageList;

void CreateList(int numOfMess)
{
    lis->clear();
    for (int i = 0; i < numOfMess; i++)
    {
        int r = rand();

        Message* mes = new Message();
        mes->ID = rand() % (10*numOfMess);
        mes->type = r % 5;
        mes->spamRating = ((double)r / RAND_MAX);
        mes->sender = random_text(r % 10 + 5);
        mes->receiver = random_text(r % 10 + 5);
        mes->text = random_text(r % 200 + 50);
        mes->sendingTime = randomTime(r);

        lis->append(mes);
    }
}

#if __has_include(<benchmark/benchmark.h>)
static void BM_QuickSort(benchmark::State& state)
{
    CreateList(state.range(0));
    SortingField field[5] = { type, sendingTime, ID, spamRating };

    for (auto _ : state) {
        lis->qSortList(nullptr, nullptr, field);
    }
}
BENCHMARK(BM_QuickSort)->RangeMultiplier(10)->Range(1 << 1, 1000000)->Iterations(1);

static void BM_CountingSort(benchmark::State& state)
{
    CreateList(state.range(0));

    for (auto _ : state) {
        lis->CountingSort();
    }
}
BENCHMARK(BM_CountingSort)->RangeMultiplier(10)->Range(1 << 1, 1000000)->Iterations(1);


static void BM_RadixSort(benchmark::State& state)
{
    CreateList(state.range(0));

    for (auto _ : state) {
        lis->RadixSort();
    }

    //system("PAUSE");
}

BENCHMARK(BM_RadixSort)->RangeMultiplier(10)->Range(1 << 1, 1000000)->Iterations(1);

#elif

//2022 - 04 - 19T00:55 : 05 + 03 : 00
//Running D : \Univercity\1_kurs\OOP_Basic\Sort_lab3\Lab3_a\Release\Lab3_b.exe
//Run on(8 X 1996 MHz CPU s)
//CPU Caches :
//L1 Data 32 KiB(x8)
//L1 Instruction 32 KiB(x8)
//L2 Unified 512 KiB(x8)
//L3 Unified 4096 KiB(x2)
//------------------------------------------------------------------------------ -
//Benchmark                                     Time             CPU   Iterations
//------------------------------------------------------------------------------ -
//BM_QuickSort / 2 / iterations:1                  5000 ns        0.000 ns            1
//BM_QuickSort / 10 / iterations : 1               8300 ns        0.000 ns            1
//BM_QuickSort / 100 / iterations : 1              8900 ns        0.000 ns            1
//BM_QuickSort / 1000 / iterations : 1           159300 ns        0.000 ns            1
//BM_QuickSort / 10000 / iterations : 1         2286700 ns        0.000 ns            1
//BM_QuickSort / 100000 / iterations : 1      613690800 ns    625000000 ns            1
//BM_QuickSort / 1000000 / iterations : 1  91151521600 ns   90906250000 ns            1
// 
//BM_CountingSort / 2 / iterations:1               8000 ns        0.000 ns            1
//BM_CountingSort / 10 / iterations : 1            9000 ns        0.000 ns            1
//BM_CountingSort / 100 / iterations : 1          19600 ns        0.000 ns            1
//BM_CountingSort / 1000 / iterations : 1        158300 ns        0.000 ns            1
//BM_CountingSort / 10000 / iterations : 1      1690900 ns        0.000 ns            1
//BM_CountingSort / 100000 / iterations : 1    14681200 ns     15625000 ns            1
//BM_CountingSort / 1000000 / iterations : 1  152727400 ns    156250000 ns            1
// 
//BM_RadixSort / 2 / iterations : 1               15500 ns        0.000 ns            1
//BM_RadixSort / 10 / iterations : 1               4200 ns        0.000 ns            1
//BM_RadixSort / 100 / iterations : 1             31400 ns        0.000 ns            1
//BM_RadixSort / 1000 / iterations : 1           331200 ns        0.000 ns            1
//BM_RadixSort / 10000 / iterations : 1         4684400 ns        0.000 ns            1
//BM_RadixSort / 100000 / iterations : 1       70920400 ns     78125000 ns            1
//BM_RadixSort / 1000000 / iterations : 1     759744600 ns    765625000 ns            1



int main()
{

    MessageList* list = new MessageList();
    list->append(getMessage());
    list->append(getMessage());
    list->append(getMessage());
    list->append(getMessage());
    list->append(getMessage());
    list->printAll();

    SortingField* fields = new SortingField[2];
    fields[0] = ID; fields[1] = spamRating;

    // 1 Task

    list->qSortList(nullptr, nullptr, fields);

    // 2 Task
    //list->RadixSort();
    //list->CountingSort();
    list->printAll();

}

#endif

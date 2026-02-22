
#if __has_include(<benchmark/benchmark.h>)
#pragma comment(lib, "Shlwapi.lib")
#include <benchmark/benchmark.h>
#endif
#include <random>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "sorting/list/message_list_sorts.hpp"

std::string str("0123456789ABCDEFGHIJK.,.effrg3g33g3.3g3,r.g,/22f2f2f77372%$@&!@#$%^&*()hhfjfdjfjdu8ududjjhGYGYFJFDJIJilhlhudhudjhjhegeydyuegdgejdgeyjgdjygEJhgdyegdyuetduyegfFGUFIGYKGJGJFJFJGFHDGEJHDGEHKDGJEGFKJEGHGhjegy3t6t6!@#$%^&*()_!@#$%^&*()_++\\?><<dhgigegkegfkgkegkfgekgfkeLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

std::random_device rd;
std::mt19937 generator(rd());

std::string random_text(int r)
{
    std::shuffle(str.begin(), str.end(), generator);
    return str.substr(0, r);
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
}

BENCHMARK(BM_RadixSort)->RangeMultiplier(10)->Range(1 << 1, 1000000)->Iterations(1);

BENCHMARK_MAIN();

#else

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

    list->qSortList(nullptr, nullptr, fields);

    list->printAll();
}

#endif

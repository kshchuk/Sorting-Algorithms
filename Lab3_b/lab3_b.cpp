//class NodeList from Lab 1
//protected:
//	struct Node
//	{
//		Message* data;
//		Node* next;
//
//		Node(Message* data);
//	};
//
//	Node* head = nullptr;
//	Node* tail = nullptr;
//}
// 
//struct Message
//{
//	int ID;
//	int type;
//	double spamRating;
//	std::string sender;
//	std::string receiver;
//	std::string text;
//	Time* sendingTime;
//}

#include <iostream>
#include "NodeList.h"
#include "Message.h"
#include "myTime.h"
#include <vector>

enum SortingField { ID, type, spamRating, sendingTime };

class MessageList : public NodeList
{
private:
    Node* FindMaxType()
    {
        Node* iter = head;
        Node* maxType = head;
        while (iter) {
            if (iter->data->type > maxType->data->type)
                maxType = iter;
            iter = iter->next;
        }
        return maxType;
    }
    Node* FindMaxID()
    {
        Node* iter = head;
        Node* maxId = head;
        while (iter) {
            if (iter->data->ID > maxId->data->ID)
                maxId = iter;
            iter = iter->next;
        }
        return maxId;
    }
    size_t GetSize()
    {
        Node* iter = head;
        size_t size = 0;
        while (iter) {
            size++;
            iter = iter->next;
        }
        return size;
    }
    size_t NumDigits(int n)
    {
        if (n < 10)
            return 1;

        size_t i = 1;
        while (n > pow(10, i))
            i++;
        return i;
    }

    // true - mes1->field > mes2->field, false otherwise
    bool Comparison(Message* mes1, Message* mes2, SortingField* fields)
    {
        switch (*fields)
        {
        case ID:
            if (mes1->ID > mes2->ID)
                return true;
            else
                if (mes1->ID == mes2->ID)
                    return Comparison(mes1, mes2, ++fields);
                else
                    return false;
            break;

        case type:
            if (mes1->type > mes2->type)
                return true;
            else
                if (mes1->type == mes2->type)
                    return Comparison(mes1, mes2, ++fields);
                else
                    return false;
            break;

        case spamRating:
            if (mes1->spamRating > mes2->spamRating)
                return true;
            else
                if (mes1->spamRating == mes2->spamRating)
                    return Comparison(mes1, mes2, ++fields);
                else
                    return false;
            break;

        case sendingTime:
            if (mes1->sendingTime > mes2->sendingTime)
                return true;
            else
                if (mes1->sendingTime == mes2->sendingTime)
                    return Comparison(mes1, mes2, ++fields);
                else
                    return false;
            break;

        default:
            return false;
            break;
        }
    }

    //Parition for quiksort of lists
    //Set of given last node position to its proper position
    Node* Parition(Node* start, Node* end, SortingField* sortingFields)
    {
        Node* pivot = start;
        Node* front = start;
        while (front && front != end)
        {
            if (Comparison(end->data, front->data, sortingFields))
            {
                pivot = start;
                std::swap(start->data, front->data);
                start = start->next;
            }
            front = front->next;
        }
        //Change last node value to current node
        std::swap(start->data, end->data);
        return pivot;
    }

public:
    // quick sort for linked list
    void qSortList(Node* start, Node* end, SortingField* sortingFieds)
    {
        if (start == nullptr || end == nullptr) {
            start = head; end = tail;
        }
        if (start == end)
            return;

        Node* pivot = Parition(start, end, sortingFieds);

        if (pivot && pivot->next)
            qSortList(pivot->next, end, sortingFieds);
        if (pivot && start != pivot)
            qSortList(start, pivot, sortingFieds);
    }

    // pigeonhole sorting, counting sort 
    // sort by type of message
    void CountingSort()
    {
        size_t maxType = FindMaxType()->data->type;
        MessageList* counts = new MessageList[maxType + 1];

        Node* iter = head;
        while (iter)
        {
            counts[iter->data->type].append(iter->data);
            iter = iter->next;
        }

        this->clear();
        for (size_t i = 0; i < maxType + 1; i++)
        {
            iter = counts[i].head;
            while (iter) {
                this->append(iter->data);
                iter = iter->next;
            }
        }
        delete[] counts;
    }

    // sorts by id
    void RadixSort()
    {
        size_t size = this->GetSize();
        int maxId = this->FindMaxID()->data->ID;
        size_t maxDigits = NumDigits(maxId);

        // creating buckets to store the pointers
        // array of pointers to linked list of size 10 as
        // integers are decimal numbers so they can hold numbers
        // from 0-9 only, that's why size of 10

        MessageList* bins = new MessageList[10];

        // first loop working for a constant time only and inner
        // loop is iterating through the array to store elements
        // of array in the linked list by their digits value
        for (size_t i = 0; i < maxDigits; i++)
        {
            Node* iter = head;
            while (iter)
            {
                bins[(iter->data->ID / (int)pow(10, i)) % 10].append(iter->data);
                iter = iter->next;
            }
        }
        this->clear();
        for (size_t i = 0; i < 10; i++)
        {
            Node* iter = bins[i].head;
            while (iter)
            {
                this->append(iter->data);
                iter = iter->next;
            }
        }
        delete[] bins;
    }
};

#pragma comment ( lib, "Shlwapi.lib" )
#include <benchmark/benchmark.h>                // https://github.com/google/benchmark
#include <random>
#include <cstdlib>

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
//BM_QuickSort / 2 / iterations:1                5000 ns        0.000 ns            1
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



//int main()
//{
//
//    MessageList* list = new MessageList();
//    list->append(getMessage());
//    list->append(getMessage());
//    list->append(getMessage());
//    list->append(getMessage());
//    list->append(getMessage());
//    list->printAll();
//
//    SortingField* fields = new SortingField[2];
//    fields[0] = ID; fields[1] = spamRating;
//
//    //list->qSortList(nullptr, nullptr, fields);
//    //list->RadixSort();
//    //list->CountingSort();
//    list->printAll();
//
//}

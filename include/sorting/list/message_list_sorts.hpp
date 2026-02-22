#pragma once

#include "NodeList.h"
#include "Message.h"
#include "myTime.h"
#include <vector>
#include <cmath>
#include <algorithm>

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
        while (n > static_cast<int>(pow(10, i)))
            i++;
        return i;
    }

    bool Comparison(Message* mes1, Message* mes2, SortingField* fields)
    {
        switch (*fields)
        {
        case ID:
            if (mes1->ID > mes2->ID)
                return true;
            else if (mes1->ID == mes2->ID)
                return Comparison(mes1, mes2, ++fields);
            else
                return false;

        case type:
            if (mes1->type > mes2->type)
                return true;
            else if (mes1->type == mes2->type)
                return Comparison(mes1, mes2, ++fields);
            else
                return false;

        case spamRating:
            if (mes1->spamRating > mes2->spamRating)
                return true;
            else if (mes1->spamRating == mes2->spamRating)
                return Comparison(mes1, mes2, ++fields);
            else
                return false;

        case sendingTime:
            if (mes1->sendingTime > mes2->sendingTime)
                return true;
            else if (mes1->sendingTime == mes2->sendingTime)
                return Comparison(mes1, mes2, ++fields);
            else
                return false;

        default:
            return false;
        }
    }

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
        std::swap(start->data, end->data);
        return pivot;
    }

public:
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

    void RadixSort()
    {
        size_t size = this->GetSize();
        int maxId = this->FindMaxID()->data->ID;
        size_t maxDigits = NumDigits(maxId);

        MessageList* bins = new MessageList[10];

        for (size_t i = 0; i < maxDigits; i++)
        {
            Node* iter = head;
            while (iter)
            {
                bins[(iter->data->ID / static_cast<int>(pow(10, i))) % 10].append(iter->data);
                iter = iter->next;
            }
            this->clear();
            for (size_t b = 0; b < 10; b++)
            {
                Node* it = bins[b].head;
                while (it)
                {
                    this->append(it->data);
                    it = it->next;
                }
                bins[b].head = nullptr;
                bins[b].tail = nullptr;
            }
        }
        delete[] bins;
    }
};

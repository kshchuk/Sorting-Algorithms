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
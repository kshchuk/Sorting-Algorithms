#include "MySorts.hpp"


// 10. Реалізувати алгоритм сортування heap sort


template <typename T>
void heapify(T arr[], int n, int i)
{
    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        heapify<T>(arr, n, largest);
    }
}

template<typename T>
void heapSort(T arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {

        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}



// 27. (***) Реалізувати паралельну версію алгоритму сортування quicksort. Порівняти з послідовною реалізацією того ж алгоритму, а також з бібліотечним алгоритмом сортування.


#include <iostream>
#include <time.h>
#include <thread>
#include <random>

#if defined (WIN32) || (_WIN64)

#include <windows.h>
#define pthread_t DWORD
#define pthread_create(THREAD_ID_PTR, ATTR, ROUTINE, PARAMS) CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ROUTINE,(void*)PARAMS,0,THREAD_ID_PTR)
#define sleep(ms) Sleep(ms)

#else // Linux

#include <pthread.h>
#include <unistd.h>

#endif

template<typename T>
class QS
{
public:
	T* c_array;
	int c_size;
	int c_thread_id;
	QS** c_threads;

	QS(T* array, int size, QS** threads, int thread_id)
	{
		c_array = array;
		c_size = size;
		c_threads = threads;
		c_thread_id = thread_id;
		threads[thread_id] = this;
	}

	~QS()
	{
		c_threads[c_thread_id] = nullptr;
	}
};

template<typename T>
void* qsort_thread(void* obj)
{
	QuickSort(((QS*)obj)->c_array, ((QS*)obj)->c_size);
	delete ((QS*)obj);
	return nullptr;
}

template<typename T>
struct RAND
{
	T* s_array;
	int s_size;

	RAND(T* array, int size)
	{
		s_array = array;
		s_size = size;
	}
};

int RANDOM_THREAD_COUNT = 0;

template<typename T>
void* randomize_thread(void* obj)
{
	RAND* r = (RAND*)obj;
	for (int i = 0; i < r->s_size; i++)
		r->s_array[i] = rand();
	delete (RAND*)r;
	RANDOM_THREAD_COUNT--;
	return nullptr;
}


template<typename T>
void QuickSortThreaded(T* g_array, const int arrSize)
{
	char* sz;

	int MAX_THREADS = std::thread::hardware_concurrency();
	if (MAX_THREADS < 1)
		MAX_THREADS = 1;

	int len = arrSize / MAX_THREADS;

	// create threads
	for (int i = 0, ai = 0; i < MAX_THREADS; i++, ai += len)
	{
		RANDOM_THREAD_COUNT++;
		pthread_t t;
		int size = len + (i == (MAX_THREADS - 1) ? (arrSize % MAX_THREADS) : 0);
		//pthread_create(&t, 0, randomize_thread, new RAND(&g_array[ai], size));
	}

	// join all current randomizing threads
	while (RANDOM_THREAD_COUNT)
		sleep(10);

	// allocate mmeory for threads
	QS** threads = new QS * [MAX_THREADS];

	clock_t time = clock();

	// create threads for qsort
	for (int i = 0, ai = 0; i < MAX_THREADS; i++, ai += len)
	{
		threads[i] = nullptr;
		pthread_t t;
		int size = len + (i == (MAX_THREADS - 1) ? (arrSize % MAX_THREADS) : 0);
		pthread_create(&t, 0, qsort_thread, new QS(&g_array[ai], size, threads, i));
	}

	// join all current threads
	for (int i = 0; i < MAX_THREADS;)
	{
		sleep(10);
		if (threads[i])
			continue;
		i++;
	}

	// now that threads are finished, do a final sort on the app's main thread
	if (MAX_THREADS > 1)
		QuickSort(g_array, arrSize);
}


int main()
{
	std::random_device rd;
	std::mt19937 mersenne(rd());

	int* arr = new int[100];
	for (int i = 0; i < 100; i++)
		arr[i] = mersenne()%100;

	QuickSortThreaded(arr, 100);
	
	for (int i = 0; i < 100; i++)
		std::cout <<arr[i] << '\n';
}

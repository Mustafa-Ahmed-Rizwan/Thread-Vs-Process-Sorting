#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_SIZE 10000
#define NUM_THREADS 4
void swap2(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void *bubble_thread(void *arg)
{
    int *arr = (int *)arg;
    int i, j, temp;
    for (i = 0; i < MAX_SIZE; i++)
    {
        for (j = 0; j < MAX_SIZE - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return NULL;
}

void bubble_sort_thread(int *arr)
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, bubble_thread, (void *)arr);
    pthread_join(threadID, NULL);
}

void *selection_thread(void *arg)
{
    int *arr = (int *)arg;
    int i, j, min_idx;
    for (i = 0; i < MAX_SIZE - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < MAX_SIZE; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap2(arr, i, min_idx);
    }
    return NULL;
}

void selection_sort_thread(int *arr)
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, selection_thread, (void *)arr);
    pthread_join(threadID, NULL);
}

void *insertion_sort(void *arg)
{
    int *arr = (int *)arg;
    int i, key, j;
    for (i = 1; i < MAX_SIZE; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    return NULL;
}

void insertion_sort_thread(int *arr)
{
    pthread_t threadID;
    pthread_create(&threadID, NULL, insertion_sort, (void *)arr);
    pthread_join(threadID, NULL);
}

struct Args
{
    int *arr;
    int low;
    int high;
};

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap2(arr, i, j);
        }
    }
    swap2(arr, i + 1, high);
    return (i + 1);
}

void* quick_sort_thread(void*);

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        // Create threads for subarrays
        pthread_t left_thread, right_thread;

        pthread_create(&left_thread, NULL, quick_sort_thread, (void *)&(struct Args){arr, low, pi - 1});
	pthread_join(left_thread, NULL);
        pthread_create(&right_thread, NULL, quick_sort_thread, (void *)&(struct Args){arr, pi + 1, high});
        pthread_join(right_thread, NULL);
    }
}

void *quick_sort_thread(void *args)
{
    struct Args *arguments = (struct Args *)args;
    quick_sort(arguments->arr, arguments->low, arguments->high);
    return NULL;
}

// Entry function for quick sort using threads
void quick_sort_threaded(int arr[])
{
    quick_sort(arr, 0, MAX_SIZE - 1);
}

// Function to merge two sorted subarrays into a single sorted array
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = (int *)malloc(n1 * sizeof(int));
    int *rightArr = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

// Function to perform merge sort on a subarray
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Thread function for merge sort
void *merge_sort_thread(void *args) {
    struct Args *arguments = (struct Args *)args;
    merge_sort(arguments->arr, arguments->low, arguments->high);
    return NULL;
}

// Entry function for merge sort using threads
void merge_sort_threaded(int arr[]) {
    pthread_t threads[NUM_THREADS];
    struct Args args[NUM_THREADS];

    int len = MAX_SIZE / NUM_THREADS;
    int remainder = MAX_SIZE % NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].arr = arr;
        args[i].low = i * len;
        args[i].high = (i == NUM_THREADS - 1) ? (i + 1) * len + remainder - 1 : (i + 1) * len - 1;

        pthread_create(&threads[i], NULL, merge_sort_thread, (void *)&args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge sorted subarrays
    for (int i = 1; i < NUM_THREADS; i++) {
        merge(arr, 0, (i * len - 1 + remainder) - 1, (i + 1) * len + remainder - 1);
    }
}

#endif

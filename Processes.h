#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void swap1(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubble_process(int arr[], int size)
{
    int i, j, temp;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap1(arr, j, j + 1);
            }
        }
    }
}

void bubble_sort_process(int arr[], int size)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        bubble_process(arr, size);
        exit(0);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("Fork failed.\n");
        exit(1);
    }
}

void selection_process(int arr[], int size)
{
    int i, j, min_index;
    for (i = 0; i < size - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        swap1(arr, i, min_index);
    }
}

void selection_sort_process(int arr[], int size)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        selection_process(arr, size);
        exit(0);
    }

    else if (pid > 0)
    {
        wait(NULL);
    }

    else
    {
        printf("Fork failed.\n");
        exit(1);
    }
}

void insertion_process(int arr[], int size)
{
    int i, key, j;
    for (i = 1; i < size; i++)
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
}

void insertion_sort_process(int arr[], int size)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        insertion_process(arr, size);
        exit(0);
    }

    else if (pid > 0)
    {
        wait(NULL);
    }

    else
    {
        printf("Fork failed.\n");
        exit(1);
    }
}

int quick_partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap1(arr, i, j);
        }
    }
    swap1(arr, i + 1, high);
    return i + 1;
}

void quick_process(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = quick_partition(arr, low, high);
        quick_process(arr, low, pi - 1);
        quick_process(arr, pi + 1, high);
    }
}

void quick_sort_process(int arr[], int size)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        quick_process(arr, 0, size - 1);
        exit(0);
    }

    else if (pid > 0)
    {
        wait(NULL);
    }

    else
    {
        printf("Fork failed.\n");
        exit(1);
     }
}

void merges(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int left_arr[n1], right_arr[n2];

    for (i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        right_arr[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort_processes(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            merge_sort_processes(arr, left, mid);
            exit(0);
        } else {
            // Parent process
            merge_sort_processes(arr, mid + 1, right);
            waitpid(pid, NULL, 0);
            merges(arr, left, mid, right);
        }
    }
}

void merge_sort_process(int array[], int len)
{
    merge_sort_processes(array, 0, len - 1);
}

#endif

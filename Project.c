#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "Processes.h"
#include "Threads.h"

typedef void(FunctionPtr1)(int *, int);
typedef void(FunctionPtr2)(int *);

double measure_time_Process(FunctionPtr1 function, int *arg1, int arg2)
{
	struct timespec begin, end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
	function(arg1, arg2); // Call the function passed as an argument with provided arguments
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	// Calculate and print the time taken
	double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
	printf("Time taken to execute (Process): %lf seconds\n", time_spent);
	return time_spent;
}

double measure_time_Thread(FunctionPtr2 function, int *arg1)
{
	struct timespec begin, end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
	function(arg1); // Call the function passed as an argument with provided arguments
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	// Calculate and print the time taken
	double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
	printf("Time taken to execute (Thread): %lf seconds\n", time_spent);
	return time_spent;
}

void save_sorted_array(int array[], int len)
{
	FILE *file = fopen("sorted.txt", "w"); // Open file for writing
	if (file == NULL)
	{
		perror("Error opening file");
		exit(1);
	}

	// Write sorted array into the file
	for (int i = 0; i < len; i++)
	{
		fprintf(file, "%d\n", array[i]);
	}

	fclose(file); // Close the file
}

int main()
{
	while (1)
	{
		FILE *file = fopen("Numbers.txt", "r"); // Open file for reading
        	if (file == NULL)
        	{
                	perror("Error opening file");
                	exit(1);
        	}

        	int array1[MAX_SIZE];
        	int array2[MAX_SIZE];
		int len = 0,len2 = 0;

        	// Read numbers from file into array
        	while (fscanf(file, "%d", &array1[len]) != EOF && len < MAX_SIZE)
        	{
        	        len++;
        	}
		fseek(file , 0 , SEEK_SET);
		while (fscanf(file, "%d", &array2[len2]) != EOF && len2 < MAX_SIZE)
                {
			len2++;
                }
        	fclose(file); // Close the file
		int choice;
		printf("\n\t\t\t\t\t******************\n");
		printf("\t\t\t\t\tProcess VS Threads\n");
		printf("\t\t\t\t\t******************\n\n");
		printf("Select Sorting Algorithms To Compare B/W Process's And Thread's Efficiency.\n");
		printf("1. Bubble Sort.\n2. Selection Sort.\n3. Insertion Sort.\n4. Quick Sort.\n5. Merge Sort.\n0. Exit.\nEnter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			exit(0);
			break;
		case 1:
			if (measure_time_Process(bubble_sort_process, array1, len) < measure_time_Thread(bubble_sort_thread, array2))
			{
				printf("Process winss yaaay...\n");
			}
			else
			{
				printf("Thread winss yaaay...\n");
			}
			save_sorted_array(array2,len);
			break;
		case 2:
			if (measure_time_Process(selection_sort_process, array1, len) < measure_time_Thread(selection_sort_thread, array2))
			{
				printf("Process winss yaaay...\n");
			}
			else
			{
				printf("Thread winss yaaay...\n");
			}
			save_sorted_array(array2,len);
			break;
		case 3:
			if (measure_time_Process(insertion_sort_process, array1, len) < measure_time_Thread(insertion_sort_thread, array2))
			{
				printf("Process winss yaaay...\n");
			}
			else
			{
				printf("Thread winss yaaay...\n");
			}
			save_sorted_array(array2,len);
			break;
		case 4:
			if (measure_time_Process(quick_sort_process, array1, len) < measure_time_Thread(quick_sort_threaded, array2))
                        {
                                printf("Process winss yaaay...\n");
                        }
                        else
                        {
                                printf("Thread winss yaaay...\n");
                        }
                        save_sorted_array(array2,len);
			break;
		case 5:
			if (measure_time_Process(merge_sort_process, array1, len) < measure_time_Thread(merge_sort_threaded, array2))
                        {
                                printf("Process winss yaaay...\n");
                        }
                        else
                        {
                                printf("Thread winss yaaay...\n");
                        }
                        save_sorted_array(array2,len);
			break;
		default:
			printf("Error: Invalid Input!\n");
		}
	}
	return 0;
}

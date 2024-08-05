
# Sorting Algorithm Performance Comparison: Threads vs Processes

This project compares the performance of various sorting algorithms when implemented using threads and processes. The sorting algorithms included are Bubble Sort, Selection Sort, Insertion Sort, Quick Sort, and Merge Sort. The project measures and compares the time taken to execute these algorithms using both threads and processes.

## Project Structure

- **`project.c`**: The main file that handles the overall execution of the program, including reading input data, executing the sorting algorithms, and measuring their performance.
- **`process.c`**: Contains the implementation of sorting algorithms using processes.
- **`thread.c`**: Contains the implementation of sorting algorithms using threads.
- **`Numbers.txt`**: Input file containing random numbers to be sorted.
- **`sorted.txt`**: Output file where the sorted array is saved.

## Features

- Comparison of sorting algorithms implemented with threads and processes.
- Measurement of execution time for each sorting algorithm.
- Options to choose between different sorting algorithms for comparison.
- Saving the sorted array to an output file (`sorted.txt`).

## How to Run

1. **Compile the Code**:
   ```bash
   gcc -o sorting_project project.c process.c thread.c -lpthread
   ```

2. **Run the Program**:
   ```bash
   ./sorting_project
   ```

3. **Input File**:
   - Ensure that the `Numbers.txt` file is in the same directory as the executable.
   - The file should contain a list of random integers, one per line.

4. **Output**:
   - After running the program, the sorted array will be saved to `sorted.txt`.
   - The program will also print the execution time taken by both the process-based and thread-based implementations for each sorting algorithm.

## Dependencies

- **GCC Compiler**: Make sure you have GCC installed on your system to compile the C code.
- **Pthreads Library**: The project uses the Pthreads library for thread management.

## Algorithms Implemented

1. **Bubble Sort**
2. **Selection Sort**
3. **Insertion Sort**
4. **Quick Sort**
5. **Merge Sort**

Each algorithm is implemented twice: once using processes and once using threads, allowing for a performance comparison.

## Benefits of Using Threads for Sorting Algorithms

- **Concurrency**: Threads allow multiple parts of the sorting algorithm to run concurrently, which can significantly speed up the sorting process on multi-core processors.
- **Efficient Resource Utilization**: Threads share the same memory space, reducing overhead and improving the efficiency of resource usage.
- **Improved Performance on Large Datasets**: By parallelizing the sorting tasks, threads can handle large datasets more efficiently compared to single-threaded implementations.

## Benefits of Using Processes for Sorting Algorithms

- **Parallel Execution**: Processes run independently and can execute sorting tasks in parallel, leveraging multi-core CPUs to reduce sorting time.
- **Isolation**: Each process operates in its own memory space, providing better isolation and security, which can be advantageous for sorting large or sensitive datasets.
- **Scalability**: Processes can be distributed across different systems, making it easier to scale sorting operations across multiple machines.


## Conclusion

This project provides insights into how different sorting algorithms perform under multi-threaded and multi-process environments. By analyzing the execution times, you can determine which approach is more efficient for each sorting algorithm.

## License

This project is open-source and available under the [MIT License](LICENSE).

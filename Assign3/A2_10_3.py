#!/usr/bin/python3

"""
Date        ::: 13-Aug-2025
Team        ::: 10
Members     :::
    1. Shoaib Mohammad    (Roll No: 002311001062)
    2. Abu Darda Mallik   (Roll No: 302411001007)
    3. Sagnik Kayal       (Roll No: 002311001046)

File Name   ::: A2_10_3.py

Assignment  ::: OS LAB — Assignment 3 (Parallel Programming in Python)

Usage:
    python3 A2_10_3.py <dim> <num_processes> <mod> <print_switch>
    or
    python A2_10_3.py <dim> <num_processes> <mod> <print_switch>

All Command Line Parameter Description:
    1) dim            : Dimension of the square matrices (e.g., 3000).
    2) num_processes  : Number of parallel worker processes to spawn (e.g., 1 to 12).
    3) mod            : Modulus for random element initialization, e.g., 100.
    4) print_switch   : '1' to print matrices A, B, and C; '0' to suppress printing.

What this Program Does:
    - This program performs parallel matrix multiplication (C = A * B) for two large square matrices.
    - It accepts matrix dimension, number of processes, a modulus, and a print switch from the command line.
    - It initializes two matrices, A and B, with random unsigned 64-bit integers.
    - To achieve efficient parallelism, it uses the 'multiprocessing.Pool' initializer. The large matrices (A and B) are passed to each worker process once upon creation, avoiding the costly overhead of transferring them with every task. This leverages the copy-on-write (COW) memory behavior on Unix-like systems.
    - The rows of matrix A are split into chunks, and each worker process computes a corresponding chunk of the result matrix C.
    - It measures only the computation time using time.perf_counter(), excluding matrix initialization.

Sample Input/Output Set:
    Command:
        python3 A2_10_3.py 10 4 100 1

    Output:
        Initializing matrices...
        Initialization complete.
        Matrix A:
        [[81 60 11 71 34 22 93 91 69 42]
         [73 68 53 84 94 72  3 89 20 54]
         [35 15 54 83 23  8 43 73 34 65]
         [18 39 30 46 89 24 58 13 42 16]
         [20 94 32 43 51 18 20 18 50 12]
         [41 92 68 13 88 56 31 15 54  2]
         [64 21 21 16 97 81 25 10 74  4]
         [88 15 59 95  9 88 34 21 17  3]
         [25 41 42 33 22 69 68 75 87 28]
         [65 42 22 53 18 89 19  8 91 19]]
        Matrix B:
        [[52 16 71 44  4 91 11 50  5 57]
         [94 62  4 10 99 97 18 25 15 42]
         [22 41 87 18 64 26 14  6 75 22]
         [10 78 51 90 28 92 84 94 85 13]
         [39  7 22 97 43 14 73 98  2 40]
         [16 82 89 95 39 21  4 15 15 76]
         [88 10 13 83 45 28 36 29 45 62]
         [23 41 68 35 21 82 30 57  9 69]
         [24  6  1 32 97 43 97 49 53 52]
         [61  3 12 18 27  5  1 17 68 45]]
        Matrix C (Result):
        [[77 19 86 10 74 19 32 46 95 15]
         [16 93 83 75 79  2 99 92 68 76]
         [71 67 43 61 73 97 78 72 37 32]
         [67 86 63 60 48 53 91 11 38  9]
         [99  3 42 25 13 47 41 29 48 29]
         [73 66 33 58 79 17 63 45 42 30]
         [56 70 82 46 71 83 91  2 40 43]
         [77 41 53 36 34 33 80 57 81 50]
         [65 29 55  5 13 90 21 10  4 16]
         [98 33 23 25 61 29 27 65 31 12]]
        Elapsed Time (seconds): 0.015812
        Number of Processes: 4

Time Taken ::: System Details:

-- Benchmarking on a 12-core system with a 3000x3000 matrix --
-- Command: python3 A2_10_3.py 3000 12 100 0 --

sar -u 2 5
Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 13/08/25 _x86_64_ (12 CPU)

01:10:15 PM IST      CPU     %user     %nice   %system   %iowait    %steal     %idle
01:10:17 PM IST      all     98.50      0.00      1.50      0.00      0.00      0.00
01:10:19 PM IST      all     99.12      0.00      0.88      0.00      0.00      0.00
01:10:21 PM IST      all     99.08      0.00      0.92      0.00      0.00      0.00
01:10:23 PM IST      all     99.17      0.00      0.83      0.00      0.00      0.00
01:10:25 PM IST      all     85.44      0.00      1.10      0.00      0.00     13.46
Average:             all     96.26      0.00      1.05      0.00      0.00      2.69

cpustat 2 3
%CPU   %USR   %SYS     PID S  CPU      Time Task
99.50  99.50   0.00   15234 R   11   0m2.03s python3
99.50  99.50   0.00   15231 R    8   0m2.05s python3
99.50  99.50   0.00   15230 R    7   0m2.05s python3
99.50  99.50   0.00   15229 R    6   0m2.06s python3
99.50  99.50   0.00   15228 R    5   0m2.06s python3
99.50  99.50   0.00   15227 R    4   0m2.06s python3
99.50  99.50   0.00   15226 R    3   0m2.06s python3
99.50  99.50   0.00   15225 R    2   0m2.06s python3
99.50  99.50   0.00   15224 R    1   0m2.06s python3
99.50  99.50   0.00   15223 R    0   0m2.06s python3
99.00  99.00   0.00   15233 R   10   0m2.04s python3
99.00  99.00   0.00   15232 R    9   0m2.04s python3
 0.50   0.50   0.00    1839 R    7   1m28.2s /usr/bin/gnome-shell

 %CPU   %USR   %SYS     PID S  CPU      Time Task
99.50  99.50   0.00   15234 R   11   0m4.03s python3
99.50  99.50   0.00   15231 R    8   0m4.05s python3
99.50  99.50   0.00   15230 R    7   0m4.05s python3
99.50  99.50   0.00   15229 R    6   0m4.06s python3
99.50  99.50   0.00   15228 R    5   0m4.06s python3
99.50  99.50   0.00   15227 R    4   0m4.06s python3
99.50  99.50   0.00   15226 R    3   0m4.06s python3
99.50  99.50   0.00   15225 R    2   0m4.06s python3
99.50  99.50   0.00   15224 R    1   0m4.06s python3
99.50  99.50   0.00   15223 R    0   0m4.06s python3
99.00  99.00   0.00   15233 R   10   0m4.04s python3
99.00  99.00   0.00   15232 R    9   0m4.04s python3
 0.50   0.50   0.00    1709 R    7   1m9.33s /usr/lib/xorg/Xorg

 %CPU   %USR   %SYS     PID S  CPU      Time Task
99.50  99.50   0.00   15234 R   11   0m6.03s python3
99.50  99.50   0.00   15231 R    8   0m6.05s python3
99.50  99.50   0.00   15230 R    7   0m6.05s python3
99.50  99.50   0.00   15229 R    6   0m6.06s python3
99.50  99.50   0.00   15228 R    5   0m6.06s python3
99.50  99.50   0.00   15227 R    4   0m6.06s python3
99.50  99.50   0.00   15226 R    3   0m6.06s python3
99.50  99.50   0.00   15225 R    2   0m6.06s python3
99.50  99.50   0.00   15224 R    1   0m6.06s python3
99.50  99.50   0.00   15223 R    0   0m6.06s python3
99.00  99.00   0.00   15233 R   10   0m6.04s python3
99.00  99.00   0.00   15232 R    9   0m6.04s python3
 0.50   0.00   0.50   15240 R    7   0m0.01s cpustat


"""

import numpy as np
import multiprocessing as mp
import sys
import time

# --- Global variables for worker processes ---
# These will be populated by the init_worker function. Using globals in this
# context is the standard, efficient way to provide large, read-only data
# to all processes in a multiprocessing.Pool without re-sending it.
g_A = None
g_B = None
g_mod = None

def init_worker(A, B, mod):
    """
    Initializer for each worker process in the pool.
    It sets the global variables for the worker's lifetime.
    """
    global g_A, g_B, g_mod
    g_A = A
    g_B = B
    g_mod = mod

def multiply_chunk(rows):
    """
    Worker function to multiply a chunk of rows of matrix A with matrix B.
    It accesses matrices A and B from the global scope.
    """
    start_row, end_row = rows
    # The 'global' keyword is not needed to read from globals.
    # The calculation is done on a slice of g_A and the entirety of g_B.
    result_chunk = np.dot(g_A[start_row:end_row], g_B)
    return result_chunk % g_mod

def main():
    """
    Main function to drive the matrix multiplication.
    """
    # 1. Argument Parsing
    if len(sys.argv) != 5:
        print("Usage: python3 A2_10_3.py <dim> <num_processes> <mod> <print_switch>")
        sys.exit(1)

    try:
        dim = int(sys.argv[1])
        num_processes = int(sys.argv[2])
        mod = int(sys.argv[3])
        print_switch = int(sys.argv[4])
        if dim <= 0 or num_processes <= 0 or mod <= 0 or print_switch not in [0, 1]:
            raise ValueError
    except (ValueError, IndexError):
        print("Error: Invalid arguments. Please provide positive integers for dim, num_processes, and mod, and 0 or 1 for print_switch.")
        sys.exit(1)

    # 2. Matrix Initialization
    print("Initializing matrices...")
    # Use a fixed seed for reproducibility in sample runs if needed.

    A = np.random.randint(0, mod, size=(dim, dim), dtype=np.uint64)
    B = np.random.randint(0, mod, size=(dim, dim), dtype=np.uint64)
    print("Initialization complete.")

    # 3. Task Preparation
    # Divide the rows of matrix A among the available processes.
    # This calculation determines the size of the row chunk for each worker.
    chunk_size = (dim + num_processes - 1) // num_processes
    # Create a list of tasks, where each task is a tuple of (start_row, end_row).
    tasks = [(i, min(i + chunk_size, dim)) for i in range(0, dim, chunk_size)]

    # 4. Parallel Computation
    start_time = time.perf_counter()

    
    with mp.Pool(processes=num_processes, initializer=init_worker, initargs=(A, B, mod)) as pool:
        # The map function distributes the 'tasks' (row index tuples) to the
        # 'multiply_chunk' function running in each worker process.
        result_parts = pool.map(multiply_chunk, tasks)

    # Combine the results from all workers into the final matrix C.
    C = np.vstack(result_parts)

    # Stop the timer.
    elapsed_time = time.perf_counter() - start_time

    # 5. Output
    if print_switch == 1:
        # Configure numpy to print the full matrices without truncation.
        np.set_printoptions(threshold=sys.maxsize, linewidth=sys.maxsize)
        print("Matrix A:")
        print(A)
        print("\nMatrix B:")
        print(B)
        print("\nMatrix C (Result):")
        print(C)

    print(f"\nElapsed Time (seconds): {elapsed_time:.6f}")
    print(f"Number of Processes: {num_processes}")

if __name__ == '__main__':
    if sys.platform != 'win32':
        mp.set_start_method('fork', force=True)
    main()
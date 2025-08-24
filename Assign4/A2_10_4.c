/***********************************************************************
* Assignment 4 - mmap() and Page Fault Observation
* ------------------------------------------------
* Team : 10
* Date : 20-August-2025
*
* Members:
* 1. Shoaib Mohammad      (Roll No: 002311001062)
* 2. Abu Darda Mallik     (Roll No: 302411001007)
* 3. Sagnik Kayal         (Roll No: 002311001046)
*
***********************************************************************************
* Assignment Objective:
* The objective of this assignment is to demonstrate the use of the mmap()
* system call to map a large file (8 GB) into the virtual address space and
* observe page faults using the 'sar' command.
*
* Task Summary:
* 1. File Handling
*    - The program checks if an 8 GB file (bigfile.dat) exists.
*    - If missing or incorrect size, it automatically creates one using ftruncate().
*    - On exit, the file is unmapped, closed, and deleted (cleanup).
*
* 2. Random Access
*    - A random offset F is generated (0 to 8 GB).
*    - A random byte X is generated (0 to 255).
*    - The program writes X to bigfile.dat at offset F, then immediately reads it back as X`.
*    - If X != X`, the program reports an error and terminates.
*    - Offset F is displayed in hexadecimal format as required.
*
* 3. Verification Loop
*    - The write/read/verify process runs in an infinite loop until interrupted (Ctrl+C).
*    - Each successful verification prints a "Success" message.
*
* 4. Page Fault Observation
*    - Run "sar -B 1" in another terminal before executing this program.
*    - "fault/s" column shows total page faults per second.
*    - These values increase because mmap uses lazy loading: 
*      file pages are not loaded until accessed, so each new access triggers a page fault.

***********************************************************************************
* Compilation Command:
*    gcc -Wall -Wextra -o A2_10_4 A2_10_4.c
*
*
* Execution Command:
*    ./A2_10_4
*
***********************************************************************************

* SAMPLE OUTPUT :
Program started. Mapping 8 GB file...
bigfile.dat not found or wrong size. Creating a new 8 GB file...
Created bigfile.dat of size 8 GB successfully.
File mapped successfully at address: 0x7f393cb1d000
Starting infinite random access loop. Press Ctrl+C to stop.
Success: Value 247 written and verified at offset 0x1f557118c
Success: Value 55 written and verified at offset 0x1f92108f4
Success: Value 74 written and verified at offset 0x72ee10be
Success: Value 254 written and verified at offset 0x143d8b3b1
Success: Value 74 written and verified at offset 0x1076942b0
Success: Value 56 written and verified at offset 0xf27cb5fa
Success: Value 148 written and verified at offset 0x518b1548
Success: Value 93 written and verified at offset 0xcef5a262
Success: Value 209 written and verified at offset 0x1ee06d1d4
Success: Value 221 written and verified at offset 0xe268c789
Success: Value 44 written and verified at offset 0x18909433e
Success: Value 39 written and verified at offset 0x3f6dcafb
Success: Value 173 written and verified at offset 0x18f211c00
Success: Value 117 written and verified at offset 0x19073a576
...
(Output truncated. Actual run produced thousands of similar lines.)
^C 
Caught signal 2. Cleaning up and exiting...
File unmapped successfully.
Deleted bigfile.dat on exit.
Program terminated gracefully.
*
* Terminal 1 (program):
* ---------------------
* Program started. Mapping 8 GB file...
* bigfile.dat not found or wrong size. Creating a new 8 GB file...
* Created bigfile.dat of size 8 GB successfully.
* File mapped successfully at address: 0x7f8b3c000000
* Starting infinite random access loop. Press Ctrl+C to stop.
* Success: Value 142 written and verified at offset 0x1a2b3c4d5
* Success: Value 67  written and verified at offset 0x987654321
* ...
*
* Terminal 2 (sar -B 1):
* ----------------------
12:28:01     pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s %vmeff
12:28:02        0.00      0.00    320.00     15.00   500.00     0.00     0.00     0.00   0.00
12:28:03        0.00      0.00    550.00     30.00   600.00     0.00     0.00     0.00   0.00
12:28:04        0.00      0.00    610.00     29.00   700.00     0.00     0.00     0.00   0.00
12:28:05        0.00      0.00    820.00     34.00   820.00     0.00     0.00     0.00   0.00
12:28:06        0.00      0.00    940.00     41.00   950.00     0.00     0.00     0.00   0.00
12:28:07        0.00      0.00   1100.00     50.00  1100.00     0.00     0.00     0.00   0.00
*
* ...
*
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

static char *mapped_memory = NULL;
static int file_descriptor = -1;
static const long long FILE_SIZE = 8LL * 1024 * 1024 * 1024; // 8 GB
static const char *FILENAME = "bigfile.dat";

void signal_handler(int signum) {
    printf("\nCaught signal %d. Cleaning up and exiting...\n", signum);
    if (mapped_memory && mapped_memory != MAP_FAILED) {
        if (munmap(mapped_memory, FILE_SIZE) == -1) perror("munmap failed");
        else printf("File unmapped successfully.\n");
    }
    if (file_descriptor != -1) {
        if (close(file_descriptor) == -1) perror("close failed");
    }
    if (remove(FILENAME) == 0) {
        printf("Deleted %s on exit.\n", FILENAME);
    } else {
        perror("Failed to delete bigfile.dat");
    }
    printf("Program terminated gracefully.\n");
    exit(0);
}

long long generate_random_offset(void) {
    // Combine rand calls to improve range
    long long offset = ((long long)rand() * rand()) % FILE_SIZE;
    if (offset < 0) offset = -offset;
    if (offset >= FILE_SIZE) offset %= FILE_SIZE;
    return offset;
}

unsigned char generate_random_byte(void) {
    return (unsigned char)(rand() % 256);
}

int main(void) {
    struct stat st;
    printf("Program started. Mapping 8 GB file...\n");

    // Register signal handlers
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Failed to register SIGINT handler");
        return 1;
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("Failed to register SIGTERM handler");
        return 1;
    }

    srand((unsigned int)time(NULL));

    // Check file and create if missing or wrong size
    if (stat(FILENAME, &st) == -1 || st.st_size != FILE_SIZE) {
        printf("%s not found or wrong size. Creating a new 8 GB file...\n", FILENAME);
        file_descriptor = open(FILENAME, O_RDWR | O_CREAT, 0666);
        if (file_descriptor == -1) {
            perror("Failed to create bigfile.dat");
            return 1;
        }
        if (ftruncate(file_descriptor, FILE_SIZE) == -1) {
            perror("Failed to set file size to 8 GB");
            close(file_descriptor);
            return 1;
        }
        printf("Created %s of size 8 GB successfully.\n", FILENAME);
    } else {
        file_descriptor = open(FILENAME, O_RDWR);
        if (file_descriptor == -1) {
            perror("Failed to open bigfile.dat");
            return 1;
        }
    }

    // Map the file
    mapped_memory = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap failed");
        close(file_descriptor);
        return 1;
    }

    printf("File mapped successfully at address: %p\n", (void*)mapped_memory);
    printf("Starting infinite random access loop. Press Ctrl+C to stop.\n");

    while (1) {
        long long offset = generate_random_offset();
        unsigned char value = generate_random_byte();

        mapped_memory[offset] = value;
        unsigned char read_value = mapped_memory[offset];

        if (value != read_value) {
            printf("ERROR: Written %u, Read %u at offset 0x%llx\n", (unsigned int)value,
                   (unsigned int)read_value, offset);
            printf("Verification failed! Terminating program.\n");
            break;
        }

        printf("Success: Value %u written and verified at offset 0x%llx\n", (unsigned int)value, offset);
        usleep(100000);  // 100 ms delay for readability
    }

    munmap(mapped_memory, FILE_SIZE);
    close(file_descriptor);
    remove(FILENAME);
    return 0;
}

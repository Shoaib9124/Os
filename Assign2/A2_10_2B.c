/***********************************************************************
*
* Assignment 2, Part B - IPC using Named Pipes (FIFOs) for 1GB File Transfer.
* ----------------------------------------------------------------------
* Team          : 10
* Date          : 6-August-2025
*
* Members:
* 1. Shoaib Mohammad      (Roll No: 002311001062)
* 2. Abu Darda Mallik     (Roll No: 302411001007)
* 3. Sagnik Kayal         (Roll No: 002311001046)
*
***********************************************************************************
*
* Assignment Details: 
* -------------------
* This program demonstrates inter-process communication using two named pipes (FIFOs).
* It performs a full round-trip transfer of a 1GB file between a parent and child process.
* The program measures the total time for this double transfer and verifies data integrity.
*
* Input Description:
* ------------------
* No command-line arguments required.
*
* Output Description:
* -------------------
* - Messages indicating the progress of FIFO creation and file transfers.
* - 'ls -l' output showing the created FIFOs and the original 1GB file.
* - The total time taken for the double transfer (Parent->Child, Child->Parent).
* - Result of the file comparison (identical or different).
* - Cleanup messages for FIFOs and temporary files.
* - All system/library calls are checked with 'perror' for error handling.
*
* Compilation Command:
* gcc A2_10_2B.c -o A2_10_2B
*
* Execution Sequence:
* Run the executable:
*    ./A2_10_2B
*
* Sample Input and Output generated:
*
* Creating FIFO: /tmp/fifo_p2c
* Creating FIFO: /tmp/fifo_c2p
* ls -l output for FIFOs and original file:
* prw-rw-r-- 1 admin adminpc     0 Aug  6 12:34 /tmp/fifo_c2p
* prw-rw-r-- 1 admin adminpc   0 Aug  6 12:34 /tmp/fifo_p2c
* -rw-r--r-- 1 admin adminpc 1073741824 Aug  6 12:34 largefile.dat
*
* [Parent] Process started. PID: 6693
* [Parent] Sending 'largefile.dat' to child via /tmp/fifo_p2c...
* [Child] Process started. PID: 6696
* [Child] Waiting to receive file from parent via /tmp/fifo_p2c...
* [Parent] Finished sending file.
* [Parent] Waiting to receive file back from child via /tmp/fifo_c2p...
* [Child] Received file from parent.
* [Child] Sending file back to parent via /tmp/fifo_c2p...
* [Child] Finished sending file back. Exiting.
* [Parent] Received file back and saved as 'largefile_returned.dat'.
* [Parent] Child process has terminated.

*
* --- Verification and Results ---
* Total time for double transfer: 0.6730 seconds
* Comparing files 'largefile.dat' and 'largefile_returned.dat'...
* ✅ Success! Files are identical.
* Cleanup complete.
* --------------------------------
*
* Timing Summary (via 'time' command):
* real    0m1.188s
* user    0m0.028s
* sys     0m1.605s
*
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// --- Configuration ---
#define FIFO_P2C "/tmp/fifo_p2c" // Parent to Child FIFO
#define FIFO_C2P "/tmp/fifo_c2p" // Child to Parent FIFO
#define ORIGINAL_FILE "largefile.dat"
#define RETURNED_FILE "largefile_returned.dat"
#define FILE_SIZE (1024LL * 1024 * 1024) // 1 GB
#define BUFFER_SIZE 65536 // 64 KB buffer for efficiency

// --- Function Prototypes ---
void create_large_file(const char* filename, off_t size);
void create_fifo(const char* fifo_name);
void send_file_via_fifo(const char* fifo_name, const char* filename);
void receive_file_via_fifo(const char* fifo_name, const char* filename);
void compare_files(const char* file1, const char* file2);
void cleanup(void);

int main() {
    pid_t pid;
    clock_t start_time, end_time;

    // --- 1. Setup ---
    printf("--- Setup Phase ---\n");
    cleanup(); // Clean up any leftovers from previous runs
    create_large_file(ORIGINAL_FILE, FILE_SIZE);
    create_fifo(FIFO_P2C);
    create_fifo(FIFO_C2P);
    printf("Setup complete. Large file and FIFOs are ready.\n");
    printf("Running 'ls -l' to show file and FIFO details:\n");
    system("ls -l largefile.dat /tmp/fifo_p2c /tmp/fifo_c2p");
    printf("--------------------------------------------------\n\n");


    // --- 2. Fork Process ---
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // --- 3. Process Logic ---
    if (pid > 0) { // --- Parent Process ---
        printf("[Parent] Process started. PID: %d\n", getpid());
        start_time = clock();

        // Task 1: Send the original file to the child
        printf("[Parent] Sending '%s' to child via %s...\n", ORIGINAL_FILE, FIFO_P2C);
        send_file_via_fifo(FIFO_P2C, ORIGINAL_FILE);
        printf("[Parent] Finished sending file.\n");

        // Task 2: Receive the file back from the child
        printf("[Parent] Waiting to receive file back from child via %s...\n", FIFO_C2P);
        receive_file_via_fifo(FIFO_C2P, RETURNED_FILE);
        printf("[Parent] Received file back and saved as '%s'.\n", RETURNED_FILE);
        
        // Wait for the child process to terminate cleanly
        wait(NULL);
        printf("[Parent] Child process has terminated.\n");

        end_time = clock();
        
        // --- 4. Verification and Cleanup ---
        printf("\n--- Verification and Results ---\n");
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Total time for double transfer: %.4f seconds\n", time_taken);

        compare_files(ORIGINAL_FILE, RETURNED_FILE);
        cleanup();
        printf("Cleanup complete.\n");
        printf("--------------------------------\n");

    } else { // --- Child Process ---
        printf("[Child] Process started. PID: %d\n", getpid());

        // Task 1: Receive the file from the parent
        printf("[Child] Waiting to receive file from parent via %s...\n", FIFO_P2C);
        receive_file_via_fifo(FIFO_P2C, "child_temp_file.dat");
        printf("[Child] Received file from parent.\n");

        // Task 2: Send the file back to the parent
        printf("[Child] Sending file back to parent via %s...\n", FIFO_C2P);
        send_file_via_fifo(FIFO_C2P, "child_temp_file.dat");
        printf("[Child] Finished sending file back. Exiting.\n");
        
        // Clean up the temporary file used by the child
        unlink("child_temp_file.dat");
        exit(EXIT_SUCCESS); // Child exits after its work is done
    }

    return 0;
}

/**
 * Sends a file's contents through a named pipe.
 */
void send_file_via_fifo(const char* fifo_name, const char* filename) {
    int fd_fifo, fd_file;
    static char buffer[BUFFER_SIZE]; // Use static for performance
    ssize_t bytes_read;

    fd_file = open(filename, O_RDONLY);
    if (fd_file == -1) {
        perror("send: open source file failed");
        exit(EXIT_FAILURE);
    }

    // Open FIFO for writing. This will block until a reader opens the other end.
    fd_fifo = open(fifo_name, O_WRONLY);
    if (fd_fifo == -1) {
        perror("send: open FIFO for writing failed");
        close(fd_file);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd_file, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_fifo, buffer, bytes_read) != bytes_read) {
            perror("send: write to FIFO failed");
            break;
        }
    }

    close(fd_file);
    close(fd_fifo); // Closing the write-end signals EOF to the reader.
}


void receive_file_via_fifo(const char* fifo_name, const char* filename) {
    int fd_fifo, fd_file;
    static char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Open FIFO for reading. This will block until a writer opens the other end.
    fd_fifo = open(fifo_name, O_RDONLY);
    if (fd_fifo == -1) {
        perror("receive: open FIFO for reading failed");
        exit(EXIT_FAILURE);
    }

    fd_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_file == -1) {
        perror("receive: open destination file failed");
        close(fd_fifo);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd_fifo, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_file, buffer, bytes_read) != bytes_read) {
            perror("receive: write to destination file failed");
            break;
        }
    }

    close(fd_file);
    close(fd_fifo);
}

/**
 *Creates a large file of a specified size.
 */
void create_large_file(const char* filename, off_t size) {
    printf("Creating a 1GB file named '%s'. This may take a moment...\n", filename);
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("create_large_file failed");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

/**
 * Creates a FIFO if it doesn't exist.
 */
void create_fifo(const char* fifo_name) {
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }
    printf("FIFO created: %s\n", fifo_name);
}

/**
 * Compares two files using the 'cmp' system command.
 */
void compare_files(const char* file1, const char* file2) {
    char command[1024];
    sprintf(command, "cmp %s %s", file1, file2);
    
    printf("Comparing files '%s' and '%s'...\n", file1, file2);
    int status = system(command);

    if (status == 0) {
        printf("✅ Success! Files are identical.\n");
    } else {
        printf("❌ Failure! Files are different or an error occurred.\n");
    }
}

/**
 * Cleans up created files and FIFOs.
 */
void cleanup(void) {
    unlink(ORIGINAL_FILE);
    unlink(RETURNED_FILE);
    unlink(FIFO_P2C);
    unlink(FIFO_C2P);
    unlink("child_temp_file.dat"); // Also clean up child's temp file
}

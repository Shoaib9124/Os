/**********************************************************************************
*
* ASSIGNMENT 1B: Get and Set Environment Variables
* ------------------------------------------------
* Team          : 10
* Date          : 23-July-2025
*
* Members:
* 1. Shoaib Mohammad      (Roll No: 002311001062)
* 2. Abu Darda Mallik     (Roll No: 302411001007)
* 3. Sagnik Kayal         (Roll No: 002311001046)
*
***********************************************************************************
*
* ASSIGNMENT DETAILS:
* A C program to demonstrate the use of getenv() and setenv() system calls.
* It first retrieves and displays a list of standard environment variables.
* Then, it sets two new custom environment variables and displays them to
* verify they have been set correctly.
*
* INPUT DESCRIPTION:
* This program does not require any command-line or interactive input.
* But follows the command-line argument format to comply with guidelines.
*
* OUTPUT DESCRIPTION:
* The program first prints the values of several predefined environment
* variables (USER, HOME, PATH, etc.). If a variable is not set, it
* indicates that. Afterwards, it sets two new variables, 'COURSE' and
* 'ASSIGNMENT_NO', and prints their newly assigned values.
*
***********************************************************************************
*
* COMPILATION:
* gcc -Wall A2_10_1B.c -o A2_10_1B
*
* EXECUTION:
* ./A2_10_1B
*
***********************************************************************************
*
* SAMPLE INPUT:
* (No Input)
*
* SAMPLE OUTPUT:
*
* --- Reading Environment Variables using getenv() ---
*
* USER = be2362
* HOME = /home/usr/student/ug/yr23/be2362
* HOST is not set.
* ARCH is not set.
* DISPLAY is not set.
* PRINTER is not set.
* PATH = /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be2362/.local/bin:/home/usr/student/ug/yr23/be2362/bin
*
*
* --- Setting New Environment Variables using setenv() ---
*
* New variable 'COURSE' set to 'OS_LAB'
* New variable 'ASSIGNMENT_NO' set to '1B'
*
*
* --- Verifying New Variables ---
*
* COURSE = OS_LAB
* ASSIGNMENT_NO = 1B
*
**********************************************************************************/

#include <stdio.h>    // For standard input-output functions like printf
#include <stdlib.h>   // For getenv() and setenv() system calls

// A helper function to get and print an environment variable
void print_env_variable(const char* var_name) {
    char* value = getenv(var_name);
    if (value != NULL) {
        printf("%s = %s\n", var_name, value);
    } else {
        printf("%s is not set.\n", var_name);
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // Array of standard environment variable names to retrieve
    const char* std_vars[] = {
        "USER", "HOME", "HOST", "ARCH", "DISPLAY", "PRINTER", "PATH"
    };
    int num_std_vars = sizeof(std_vars) / sizeof(std_vars[0]);

    printf("\n--- Reading Environment Variables using getenv() ---\n\n");

    // Loop through the array and print each standard variable
    for (int i = 0; i < num_std_vars; i++) {
        print_env_variable(std_vars[i]);
    }

    printf("\n\n--- Setting New Environment Variables using setenv() ---\n\n");

    // Set two new environment variables.
    // The '1' indicates to overwrite the variable if it already exists.
    if (setenv("COURSE", "OS_LAB", 1) == 0) {
        printf("New variable 'COURSE' set to 'OS_LAB'\n");
    } else {
        perror("Error setting variable 'COURSE'");
    }

    if (setenv("ASSIGNMENT_NO", "1B", 1) == 0) {
        printf("New variable 'ASSIGNMENT_NO' set to '1B'\n");
    } else {
        perror("Error setting variable 'ASSIGNMENT_NO'");
    }

    printf("\n\n--- Verifying New Variables ---\n\n");

    // Verify the new variables by reading them back with getenv()
    print_env_variable("COURSE");
    print_env_variable("ASSIGNMENT_NO");

    printf("\n");

    return 0;
}


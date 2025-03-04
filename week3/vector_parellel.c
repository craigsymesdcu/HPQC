#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // Include OpenMP header

// Function declarations
int check_args(int argc, char **argv);
void initialise_vector(int vector[], int size, int initial);
void print_vector(int vector[], int size);
int sum_vector(int vector[], int size);

int main(int argc, char **argv)
{
    // Check and parse command-line arguments
    int num_arg = check_args(argc, argv);

    // Allocate memory for the vector
    int* my_vector = malloc(num_arg * sizeof(int));
    if (my_vector == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed!\n");
        exit(-1);
    }

    // Initialize the vector with a sequence of numbers
    initialise_vector(my_vector, num_arg, 0);

    // Print the vector (optional, for verification)
    printf("Initialized vector:\n");
    print_vector(my_vector, num_arg);

    // Sum the vector in parallel
    int my_sum = sum_vector(my_vector, num_arg);

    // Print the sum
    printf("Sum: %d\n", my_sum);

    // Free allocated memory
    free(my_vector);

    return 0;
}

// Function to sum a vector of integers in parallel
int sum_vector(int vector[], int size)
{
    int sum = 0;

    // Use OpenMP to parallelize the summation
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++)
    {
        sum += vector[i];
    }

    return sum;
}

// Function to initialize all values in a vector to a given initial value
void initialise_vector(int vector[], int size, int initial)
{
    for (int i = 0; i < size; i++)
    {
        vector[i] = initial + i; // Initialize with a sequence of numbers
    }
}

// Function to print a vector of integers
void print_vector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", vector[i]);
    }
}

// Function to check command-line arguments
int check_args(int argc, char **argv)
{
    int num_arg = 0;

    if (argc == 2) // Program name and numerical argument
    {
        num_arg = atoi(argv[1]);
        if (num_arg <= 0) // Validate the argument
        {
            fprintf(stderr, "ERROR: The numerical argument must be a positive integer!\n");
            exit(-1);
        }
    }
    else // Incorrect number of arguments
    {
        fprintf(stderr, "ERROR: You did not provide a numerical argument!\n");
        fprintf(stderr, "Correct use: %s [NUMBER]\n", argv[0]);
        exit(-1);
    }

    return num_arg;
}
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

// Function prototypes
void initialize_mpi(int *argc, char ***argv, int *rank, int *size);
void check_communicator_size(int size);
void handle_root_process(int rank, int size);
void handle_non_root_process(int rank);
void finalize_mpi();

int main(int argc, char **argv) 
{
    int rank, size;

    // Initialize MPI and get rank and size
    initialize_mpi(&argc, &argv, &rank, &size);

    // Check if the communicator size is sufficient
    check_communicator_size(size);

    // Handle logic based on process rank
    if (rank == 0) 
    {
        handle_root_process(rank, size);
    } 
    else 
    {
        handle_non_root_process(rank);
    }

    // Finalize MPI
    finalize_mpi();

    return 0;
}

// Function to initialize MPI and retrieve rank and size
void initialize_mpi(int *argc, char ***argv, int *rank, int *size) 
{
    int ierror = MPI_Init(argc, argv);
    ierror = MPI_Comm_rank(MPI_COMM_WORLD, rank);
    ierror = MPI_Comm_size(MPI_COMM_WORLD, size);

    // Error handling (optional)
    if (ierror != MPI_SUCCESS) 
    {
        fprintf(stderr, "Error initializing MPI or retrieving rank/size.\n");
        MPI_Abort(MPI_COMM_WORLD, ierror);
    }
}

// Function to check if the communicator size is sufficient
void check_communicator_size(int size) 
{
    if (size <= 1) 
    {
        printf("Unable to communicate with less than 2 processes. MPI communicator size = %d\n", size);
        MPI_Finalize();
        exit(1); // Exit the program if there are not enough processes
    }
}

// Function to handle the root process (rank 0)
void handle_root_process(int rank, int size) 
{
    int recv_message, count = 1, tag = 0;
    MPI_Status status;

    // Iterate through all other ranks and receive messages
    for (int source = 1; source < size; source++) 
    {
        MPI_Recv(&recv_message, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("Hello, I am %d of %d. Received %d from Rank %d\n", rank, size, recv_message, source);
    }
}

// Function to handle non-root processes (rank > 0)
void handle_non_root_process(int rank) 
{
    int send_message, count = 1, dest = 0, tag = 0;

    // Create the message (rank * 10)
    send_message = rank * 10;

    // Send the message to the root process
    MPI_Send(&send_message, count, MPI_INT, dest, tag, MPI_COMM_WORLD);

    // Print the sent message
    printf("Hello, I am %d. Sent %d to Rank %d\n", rank, send_message, dest);
}

// Function to finalize MPI
void finalize_mpi() 
{
    int ierror = MPI_Finalize();

    // Error handling (optional)
    if (ierror != MPI_SUCCESS) 
    {
        fprintf(stderr, "Error finalizing MPI.\n");
    }
}
Activity for Topic 4: MPI Communications
Part 1: Demonstrating Communications
Step 1: Run the code as-is

compile with  : mpicc HPQC/week4/comm_test_mpi.c -o bin/comm_test_mpi

symesc2@cheetah:~$ mpirun bin/comm_test_mpi

Run profile example :

No protocol specified
Hello, I am 9 of 16. Sent 90 to Rank 0
Hello, I am 13 of 16. Sent 130 to Rank 0
Hello, I am 5 of 16. Sent 50 to Rank 0
Hello, I am 1 of 16. Sent 10 to Rank 0
Hello, I am 11 of 16. Sent 110 to Rank 0
Hello, I am 15 of 16. Sent 150 to Rank 0
Hello, I am 2 of 16. Sent 20 to Rank 0
Hello, I am 3 of 16. Sent 30 to Rank 0
Hello, I am 8 of 16. Sent 80 to Rank 0
Hello, I am 12 of 16. Sent 120 to Rank 0
Hello, I am 7 of 16. Sent 70 to Rank 0
Hello, I am 6 of 16. Sent 60 to Rank 0
Hello, I am 14 of 16. Sent 140 to Rank 0
Hello, I am 10 of 16. Sent 100 to Rank 0
Hello, I am 4 of 16. Sent 40 to Rank 0
Hello, I am 0 of 16. Received 10 from Rank 1
Hello, I am 0 of 16. Received 20 from Rank 2
Hello, I am 0 of 16. Received 30 from Rank 3
Hello, I am 0 of 16. Received 40 from Rank 4
Hello, I am 0 of 16. Received 50 from Rank 5
Hello, I am 0 of 16. Received 60 from Rank 6
Hello, I am 0 of 16. Received 70 from Rank 7
Hello, I am 0 of 16. Received 80 from Rank 8
Hello, I am 0 of 16. Received 90 from Rank 9
Hello, I am 0 of 16. Received 100 from Rank 10
Hello, I am 0 of 16. Received 110 from Rank 11
Hello, I am 0 of 16. Received 120 from Rank 12
Hello, I am 0 of 16. Received 130 from Rank 13
Hello, I am 0 of 16. Received 140 from Rank 14
Hello, I am 0 of 16. Received 150 from Rank 15

The prognam appears to check if there are more than 1 process . If ther are multiple process Rank 0 acts a s the crciver.
There is iteration through all ather ranks. Then the message is recived and printed. Non 0 ranks act as senders . There message is there rank multiplied by 10.
Step 2: Functionalise the code
see :
comm_test_mpi_modified.c

symesc2@cheetah:~$ mpirun -np 4 bin/comm_test_modified
No protocol specified
Hello, I am 1. Sent 10 to Rank 0
Hello, I am 2. Sent 20 to Rank 0
Hello, I am 0 of 4. Received 10 from Rank 1
Hello, I am 0 of 4. Received 20 from Rank 2
Hello, I am 0 of 4. Received 30 from Rank 3
Hello, I am 3. Sent 30 to Rank 0

Step 3: Experiment with send types
see :
comm_test_mpi_send_types.c

I observed some segmentation faults and variable declaration errors. 
MPI program is crashing with a segmentation fault (signal 11).
Warning: No send type specified. Using default value 0 (MPI_Send).

Out put : 
symesc2@cheetah:~$ mpirun -np 6 bin/comm_test_send_types
No protocol specified
Warning: No send type specified. Using default value 0 (MPI_Send).
Warning: No send type specified. Using default value 0 (MPI_Send).
Warning: No send type specified. Using default value 0 (MPI_Send).
Warning: No send type specified. Using default value 0 (MPI_Send).
Hello, I am 2. Sent 20 to Rank 0 using send type 0
Hello, I am 4. Sent 40 to Rank 0 using send type 0
Hello, I am 5. Sent 50 to Rank 0 using send type 0
Hello, I am 0 of 6. Received 10 from Rank 1
Hello, I am 0 of 6. Received 20 from Rank 2
Hello, I am 0 of 6. Received 30 from Rank 3
Hello, I am 0 of 6. Received 40 from Rank 4
Hello, I am 0 of 6. Received 50 from Rank 5
Hello, I am 1. Sent 10 to Rank 0 using send type 0
Warning: No send type specified. Using default value 0 (MPI_Send).
Hello, I am 3. Sent 30 to Rank 0 using send type 0
symesc2@cheetah:~$

CO


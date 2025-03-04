Part 1
Implementated hello_mpi.c
mpicc  -o hello hello_mpi.c
Esecuted hello_mpi.c with mpirun-np 4./hello
With outputs :

Hello, I am 2 of 4
Hello, I am 0 of 4
Hello, I am 3 of 4
Hello, I am 1 of 4

when MPI_Init() and oth eseal elements were not used,I the compiler would output an error message and not compile the code.

I compiled and ran hello_mpi.
the results for 4 
real    0m0.531s
user    0m0.184s
sys     0m0.214s

I ran it with a number greater than 16 it printed an error message

the results for 10
real    0m0.554s
user    0m0.371s
sys     0m0.393s

the results for 16
real    0m0.617s
user    0m0.505s
sys     0m0.664s

The sum of the user and sys times becomes greater than the real time.

Part 2
Documenting proof.c

First there is function decleration . There are some void funtions that don't return a value.
In main there is initialization and decleration. 
Root task take an intiger of uni_size . There is more initialisation.
There is an iteratining loop . From this loop there are outputs.
Perhaps there is a way to optimise the code by havig all the initilasation done on one line .
Then on a second line have a loop that prints to terminal .
All the "work" that the code is doing seems to be in the lasst 5 lines.

Part 3 

vector_serial.c documentation

First there is decleration of functions. This incudes an intiger argument , a funtion to intilise, print and sum a vector.
Then in main , you create any number of "empty" vectors that you want.
Creat some vectors that are not "empty"/zero.They are then initialised to some initial value.
the vectors are add and an output is given . This includes a memory accocation function.
sum vectors simply itterates over all the vectors adding them.

The templates performance :
Sum: 0

real    0m0.003s
user    0m0.001s
sys     0m0.002s

to do 

Modify the serial code to be non-trivial 
vector[i] = initial + i; // I added this to initilize with  a sequence of numbers 
symesc2@cheetah:~$ time bin/vector_serial 4
Sum: 6

real    0m0.002s
user    0m0.002s
sys     0m0.000s
symesc2@cheetah:~$ time bin/vector_serial 100
Sum: 4950

real    0m0.002s
user    0m0.002s
sys     0m0.000s
symesc2@cheetah:~$ time bin/vector_serial 123456789
Sum: 1206807378

real    0m0.952s
user    0m0.788s
sys     0m0.164s
symesc2@cheetah:~$ time bin/vector_serial 12345678912345678900
Sum: 0

real    0m0.002s
user    0m0.000s
sys     0m0.001s
Here it can be observed that for large numbers the code fails due to overflow error, returing 0 

Create a parallel version
see file vector_parelle.c
Benchmark and evaluate parallel against serial implementations 
It was observed that there was nolonge an overflow for large numbers . 
symesc2@cheetah:~$ time bin/vector_parellel 123456
Sum: 76193340

real    0m0.039s
user    0m0.013s
sys     0m0.026s

however some outputs gave a negative number 
symesc2@cheetah:~$ time bin/vector_parellel 123456
Sum: -969304352

real    0m0.324s
user    0m0.075s
sys     0m0.247s

Indicating some error .
This code can run for input >100000000.
It takes along time to desiplay these values 
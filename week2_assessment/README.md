# Week 2 practical

How to run the code 

time_print_write_to_file.py 
must be executed from a directory that conatains "results.txt"
you will have to manully delete the results form "results.txt2 every time

time_print_read_from_file.py 
must be executed from a directory that conatains "results.txt"
It will read everything in the file

time_print_write_to_file.c 
must be executed from a directory that conatains "results.txt"
you will have to manully delete the results form "results.txt2 every time

#time_print_read_from_file.c
must be executed from a directory that conatains "results.txt"
It will read everything in the file

Evaluate your results

Hello World 

python times :
real    0m0.032s
user    0m0.023s
sys     0m0.008s

C times :
real    0m0.015s
user    0m0.002s
sys     0m0.000s

The real times are greater that the user .The system time were the smallest. The C code was faster than the python3 code.

Repeat Adder

When both number were small the times were less than 0.17 seconds.
With one big number and one small number the times were less that 0.04 seconds.
Two big numbers resulted in times closer to zero. C was faster than python.

Time Print

Don't do time_print 1234567890! The network crashed at 355715224

for smaller the numbers the timer for loop was small~ 1e-05 seconds
real  ~  0m0.033s, user  ~ 0m0.028s and sys  ~  0m0.004s.

for 7 digit numbers the timer for loop was approximately 1 second.
with real and user times also cloe to one second.Symestem time were at 0.03 s.

For larger 7 digit numberes the times began to increse . With time for loop and real time had the biggest increase. 
Followeed by the user time. The system time remainde sub 1 second.
Fro python the loop time aperas to increase by 1 second per million.
C appears to be slower with the big numbers . This is not expected !
20 million took 35 seconds and I stopped increasing the number.

Reading and writing to text file

Writing to a file take longer than printing to terminal.
Reading from a file can be ver quickly. 
C is faster than python


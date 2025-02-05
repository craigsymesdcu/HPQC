import sys
import time

# define a funtion that reads from results.txt text file
def Readfromtext():
    # open the text file 
    g = open('results.txt','r')
    print(g.read())
    g.close()

def main(): 
     # gets the start time for the loop
    start_time = time.time()
    #read form text
    Readfromtext()
    # gets the end time for the loop
    end_time = time.time()

    # gets the total time
    run_time = end_time - start_time
    # prints the output
    print("\n\nTime for loop: {} seconds\n".format(run_time))

if __name__ == "__main__":
    main()
 
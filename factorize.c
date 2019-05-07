/**
* factorize.c: Uses OpenMP to factorize a large number (passed as a command line argument) into two primes.
* Has each thread check a certain portion of possible factors (for four threads, thread 0 would check 3, 11, 19, 27 etc.)
* Preemptively checks if even to find factor of 2, otherwise only checks odds from 3 to parameter / 2
* Checks if potential factor is prime, then if it evenly divides into the parameter, then if the parameter divided by the factor is prime
* Authors: Philip Brunet, Max Ranes
* Date: 5/2/2019
* Final Project for COMP 262 w/ Prof. Scott Feister
**/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
/**
* Checks if a long is prime
* @param candidate: long to check
* @return: true if prime, false if not
**/
bool isPrime(long candidate)
{
	if(candidate <= 1) //Can't be negative, 0, or 1
	{
		return false;
	}
	for(int i = 2; i <= candidate / 2; i++) //Can't be higher than candidate / 2
	{
		if((candidate % i) == 0) //Checks all possible factors, marking as not prime if factor is found
		{
			return false;
		}
	}	
	return true; //No factor found, must be prime
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./factorize <large multiple of two primes>\n"); //Let user know the usage if they don't give correct parameters
		return(0); //Return if no parameters or too many
	}

	long parameter = strtol(argv[1], NULL, 10); //long to hold parameter
	int nthreads;
	int tid; //ints to hold number of threads and thread IDs
	long prime1;
	long prime2; //longs to hold possible primes
	bool flag = false; //Checks if a result has been found
	#pragma omp parallel shared(nthreads,parameter, flag) private(tid, prime1, prime2) //Split into multiple threads
	{
		tid = omp_get_thread_num(); //Check the thread number
		//printf("Thread number %d checking in!\n", tid);
		if(tid == 0)
		{
			nthreads = omp_get_num_threads(); //Get number of threads
			if(parameter % 2 == 0) //If even, we alrady know the answer
			{
				flag = true;
				prime1 = 2;
				prime2 = parameter / 2;
				printf("ANSWER FOUND! %ld and %ld are the factors of %ld\n", prime1, prime2, parameter);
			}
		}
		for(prime1 = 3 + 2 * tid; !flag && prime1 <= parameter / 2; prime1 += (nthreads * 2)) //Each thread checks a portion of the primes; doesn't need to check evens
		{		
			if(isPrime(prime1)) //If not prime, continue
			{
				//printf("Checking %ld on thread %d\n", prime1, tid);
				if(((double)parameter / prime1) - (parameter / prime1) == 0 && isPrime(parameter / prime1))
				{ //Check if prime1 divides evenly, then if it's one of two prime factors
					flag = true; //Stop other threads
					prime2 = (parameter / prime1); //sets prime2 to value found by dividing parameter and prime1
					printf("ANSWER FOUND! %ld and %ld are the factors of %ld\n", prime1, prime2, parameter); //Tell user that answer was found
				}
			}
		}

	} //All threads join
	//printf("All threads successfully joined.\nThere were %d threads.\n", nthreads);
}

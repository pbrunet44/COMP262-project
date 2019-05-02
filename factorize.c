/**
* factorize.c: Uses OpenMP to factorize a large number (passed as a command line argument) into two primes.
* Authors: Philip Brunet, Max Ranes
* Date: 5/2/2019
* Final Project for COMP 262 w/ Prof. Scott Feister
**/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./factorize <large multiple of two primes>\n");
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
		tid = omp_get_thread_num();
		printf("Thread number %d checking in!\n", tid);
		if(tid == 0)
		{
			nthreads = omp_get_num_threads();
		}
		while(!flag)
		{
			prime1 = rand() % 25;
			do
			{
				prime2 = rand() % 25;
			} while(prime1 == prime2);
			printf("Checking %ld and %ld on thread %d\n", prime1, prime2, tid);
			if(prime1 * prime2 == parameter)
			{
				flag = true;
				printf("ANSWER FOUND! %ld and %ld are the factors of %ld\n", prime1, prime2, parameter);
			}
		}

	} //All threads join
	printf("All threads successfully joined.\nThere were %d threads.\n", nthreads);
}
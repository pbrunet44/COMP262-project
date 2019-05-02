/**
* factorize.c: Uses OpenMP to factorize a large number (passed as a command line argument) into two primes.
* Authors: Philip Brunet, Max Ranes
* Date: 5/2/2019
* Final Project for COMP 262 w/ Prof. Scott Feister
**/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./factorize <large multiple of two primes>\n");
		return(0); //Return if no parameters or too many
	}
	long multiple = strtol(argv[1], NULL, 10);
	

}
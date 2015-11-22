/*
 * Demonstrates the "Short circuiting" of using the golden ratio
 * to calculate fibonacci numbers.  Start by passing a low number
 * to the program such as 3 or 5, look at the metrics and then pass
 * a higher number such as 30 and then
 * note the differences in the elapsed time and number of function calls.
 * Note the elapsed time for the golden ratio method should remain
 * relatively unchanged while the elapsed time and number of function
 * calls for the recursive method both grow by enormous amounts.
 * This is known as exponential recursion and can humble even the most
 * powerful computers quite quickly.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BILLION 1000000000L

int fibGolden( int );
int fibRecursive( int, int* );

int main( int argc, char *argv[] ){
	uint64_t diff;
	struct timespec start, end;
	int counter = 0;
	
	if( argc == 2 ){

/* Runs the golden ratio fibonacci function and displays some metrics */
		int input = atoi( argv[1] );
		
		printf( "\n**GOLDEN RATIO METHOD**" );
		clock_gettime( CLOCK_MONOTONIC, &start );
		printf( "\n%d is the %dth number in the fibonacci sequence", fibGolden( input ), input );
		clock_gettime( CLOCK_MONOTONIC, &end );
		diff = BILLION * ( end.tv_sec - start.tv_sec ) + end.tv_nsec - start.tv_nsec;
		printf( "\nelapsed time = %llu nanoseconds\n", ( long long unsigned int )diff );
		
/* Runs the recursive fibonacci function and displays some metrics */
		printf( "\n**RECURSIVE METHOD**" );
		clock_gettime( CLOCK_MONOTONIC, &start );
		printf( "\n%d is the %dth number in the fibonacci sequence,", fibRecursive( input, &counter ), input );
		clock_gettime( CLOCK_MONOTONIC, &end );
		diff = BILLION * ( end.tv_sec - start.tv_sec ) + end.tv_nsec - start.tv_nsec;
		printf( "\nelapsed time = %llu nanoseconds", ( long long unsigned int )diff );
		printf( "\nMade %d recursive function calls\n\n", counter );
		return 0;
	} else {
/* If the incorrect argument is passed to the program, prints usage */
		printf( "Usage: fib [number]\n"
		"number - The indice of the fibonacci sequence to compute\n"
		"eg: fib 3\n" );
	}
}

/* Calculates the fibonacci number using the golden ratio */
int fibGolden( int n ){
	int fib;	
	double phi = ( 1 + sqrt( 5.0 ) ) / 2;
	
	fib = ( pow( phi, n ) - pow( ( -1 / phi ), n ) ) / sqrt( 5.0 );
	return fib;
}

/* Calculates the fibonacci number using recursion */
int fibRecursive( int n, int *count ){
	*count = *count + 1;
	if( n == 0 || n==1 ){
		return n;
	} else {
		return ( fibRecursive( n - 1, count ) + fibRecursive( n - 2, count ) );
	}
}

# Assignment 2

This program will compare arcsin, arccos, arc tan, and log with <math.h> library. (command options: -a run for all, -s run arcsin, -c run arcos, -t run arctan, -l run log)

## Build

	$ clang -Wall -Werror -Wpedantic -o mathlib-test mathlib-test.c
	or
	$make

## Running

	$ ./mathlib-test
	$ (input for command options described above)

## Cleaning

	$ rm -f mathlib.o mathlib-test mathlib-test.o
	or
	$ make clean

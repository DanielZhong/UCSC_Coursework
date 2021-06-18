# Assignment 1

This program simulate the game left right and center. Each player has 3 dollars, and 3 dices. If a player has 3 dollars then roll 3 times, if 2, roll 2, if 1, roll 1. There are 6 faces in the dice(L gives 1 dollar to left, R gives 1 dollar to right, C put 1 dollar to center, dot then skip(3 dots total in 1 dice)). When there is only 1 player who has money, then that player wins the game.


## Build

	$ clang -Wall -Werror -Wpedantic -o lrc lrc.c
	or
	$ make 

## Running

	$ ./lrc
	$ (input number of seeds)
	$ (input number of players)

## Cleaning
	$ rm -f lrc lrc.c
	or
	$ make clean

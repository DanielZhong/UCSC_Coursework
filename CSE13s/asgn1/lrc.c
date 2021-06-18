#include "philos.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIVES 3
typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

//return current position player to the left
static inline uint8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

//return current position player to the right
static inline uint8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

int main(void) {
    uint32_t seed = 0; //variable seed to store number of seeds
    printf("Random seed: ");
    if (scanf("%" SCNu32, &seed) != 1) { //print error message if wrong seed number
        fprintf(stderr, "Invalid seeds\n");
        return 1;
    }
    if (seed <= UINT32_MAX) { //continue to ask for number of player if correct seeds number
        srandom(seed);
        uint32_t p = 0; //variable p to store number of player
        printf("How many players? ");
        if (scanf("%" SCNu32, &p) != 1) { //error message if wrong number of player
            fprintf(stderr, "Number of players must be from 1 to 14.\n");
            return 1;
        }
        if (p >= 1 && p <= 14) { // continue to program if both seed and player numbers are correct
            int money[14] = { LIVES, LIVES, LIVES, LIVES, LIVES, LIVES, LIVES, LIVES, LIVES, LIVES,
                LIVES, LIVES, LIVES, LIVES };
            int pot = 0;

            for (uint32_t c = 0; c < p; c++) {
                for (uint32_t i = 0; i < p; i++) { //for 1 round
                    c = 0;
                    int z = 0; //variable to check number of times to dice
                    if (money[i] >= 3) {
                        z = 3;
                        printf("%s rolls...",
                            philosophers
                                [i]); //roll dice based on z(3 dollars roll 3 times, 2 dollars 2, 1 dollar 1)
                    } else if (money[i] == 2) {
                        z = 2;
                        printf("%s rolls...",
                            philosophers
                                [i]); //roll dice based on z(3 dollars roll 3 times, 2 dollars 2, 1 dollar 1)
                    } else if (money[i] == 1) {
                        z = 1;
                        printf("%s rolls...",
                            philosophers
                                [i]); //roll dice based on z(3 dollars roll 3 times, 2 dollars 2, 1 dollar 1)
                    }

                    for (
                        int x = 0; x < z;
                        x++) { //roll dice based on z(3 dollars roll 3 times, 2 dollars 2, 1 dollar 1)
                        int r = random() % 6;
                        if (die[r]
                            == LEFT) { //if left face, left position + 1 money, current player -1 money
                            money[left(i, p)] += 1;
                            money[i] -= 1;
                            printf(" gives $1 to %s", philosophers[left(i, p)]);
                        } else if (
                            die[r]
                            == RIGHT) { //if right face, left position + 1 money, current player -1 money
                            money[right(i, p)] += 1;
                            money[i] -= 1;
                            printf(" gives $1 to %s", philosophers[right(i, p)]);
                        } else if (
                            die[r]
                            == CENTER) { //if center face, pot + 1 money, current player -1 money
                            pot += 1;
                            money[i] -= 1;
                            printf(" puts $1 in the pot");
                        } else if (die[r] == PASS) { // print out pass message only if pass face
                            printf(" gets a pass");
                        }
                    }
                    if (z != 0) { //print next line if current player finished their rolled
                        printf("\n");
                    }

                    //count how many 0 money
                    for (uint32_t k = 0; k < p; k++) {
                        if (money[k] == 0) {
                            c = c + 1;
                        }
                    }
                    if (c == p - 1) { //if there is a winner, break the loop
                        break;
                    }
                }
            }

            //find the winner and print won message.
            for (uint32_t q = 0; q < p; q++) {
                if (money[q] != 0) {
                    printf("%s wins the $%d pot with $%d left in the bank!\n", philosophers[q], pot,
                        money[q]);
                }
            }
        }

        else {
            fprintf(stderr,
                "Number of players must be from 1 to 14.\n"); //continue to ask for number of player if correct seeds number
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid seeds\n"); //print error message if wrong seed number
        return 1;
    }
    return 0;
}

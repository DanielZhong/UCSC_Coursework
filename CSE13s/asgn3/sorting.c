#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h> // For bool
#include <stdint.h>
#include <stdio.h> //For printf()
#include <stdlib.h> //For atoi() and strtoul()  inspired by instructor:Eric Hernandez in question@381:https://piazza.com/class/kmfs2bmdr9syz?cid=381
#include <unistd.h> // For getopt()

#define OPTIONS         "absqQr:n:p:"
#define INPUT_BASE      10 //input has to be decimal
#define INIT_SEED       13371453 //default seed
#define INIT_ARRAY_SIZE 100 //default size
#define INIT_ELEMENT    100 //default size

typedef enum Sorting {
    bubble = 0,
    shell = 1,
    stack = 2,
    queue = 3,
} Sorting;

void array_copy(uint32_t *A, uint32_t *B, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        A[i] = B[i];
    }
}

int main(int argc, char **argv) {
    //set defualt
    int opt = 0;
    uint32_t seed = INIT_SEED, size = INIT_ARRAY_SIZE, elements = INIT_ELEMENT;
    Set sort = set_empty();
    //command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) { // enable all sort algo
        case 'a': sort = set_complement(set_empty()); break;
        case 'b': sort = set_insert(sort, bubble); break;
        case 's': sort = set_insert(sort, shell); break;
        case 'q': sort = set_insert(sort, stack); break;
        case 'Q': sort = set_insert(sort, queue); break;
        case 'r':
            seed = strtoul(optarg, NULL, INPUT_BASE); //input seed
            break;
        case 'n':
            size = strtoul(optarg, NULL, INPUT_BASE); //input size
            break;
        case 'p':
            elements = strtoul(optarg, NULL, INPUT_BASE); //input elements
            break;
        }
    }

    // create Array
    uint32_t A[size];
    // backup to shuffle A
    uint32_t B[size];
    // set the random seed
    srandom(seed); //random the seed

    for (uint32_t i = 0; i < size; i++) {
        A[i] = random();
        B[i] = A[i]; // backup
    }

    if (size < elements) { //if size smaller than elements, than shoule be equal each other
        elements = size;
    }

    for (Sorting z = bubble; z <= queue; z++) {
        if (set_member(sort, z)) {
            switch (z) {
            case bubble: //print bubble osrt and format %13
                bubble_sort(A, size);
                printf("Bubble Sort\n");
                printf("%u elements, %u moves, %u compares", size, b_move, b_compare);
                for (uint32_t i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");

                break;

            case shell:
                array_copy(A, B, size);
                shell_sort(A, size); //print shell sort and format %13
                printf("Shell Sort\n");
                printf("%u elements, %u moves, %u compares", size, s_move, s_compare);
                for (uint32_t i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");

                break;

            case stack:
                array_copy(A, B, size);
                quick_sort_stack(A, size); //print quick sort with stack method and format %13
                printf("Quick Sort (Stack)\n");
                printf("%u elements, %u moves, %u compares\n", size, q_move, q_compare);
                printf("Max stack size: %u", s_size);
                for (uint32_t i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");

                break;

            case queue:
                q_move = 0;
                q_compare = 0;
                array_copy(A, B, size);
                quick_sort_queue(A, size); //print quick sort with queue method and format %13
                printf("Quick Sort (Queue)\n");
                printf("%u elements, %u moves, %u compares\n", size, q_move, q_compare);
                printf("Max queue size: %u", q_size);
                for (uint32_t i = 0; i < elements; i++) {
                    if (i % 5 == 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
                printf("\n");

                break;
            }
        }
    }
    return 0;
}
//inspired by eugene ta section

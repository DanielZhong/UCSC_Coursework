#include "bubble.h"

#include <stdbool.h>
#include <stdint.h>

uint32_t b_compare = 0;
uint32_t b_move = 0;

void swapped(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

//followed pdf python pesudocode ideas
void bubble_sort(uint32_t *A, uint32_t n) {
    bool swap = true;
    while (swap == true) {
        swap = false;
        for (uint32_t i = 1; i < n; i++) {
            b_compare++;
            if (A[i] < A[i - 1]) {
                swapped(&A[i], &A[i - 1]); //swap two values
                b_move += 3;
                swap = true;
            }
        }
        n -= 1;
    }
}

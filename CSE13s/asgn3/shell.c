#include "shell.h"

#include "gaps.h"

#include <inttypes.h>
#include <stdio.h>

uint32_t s_move = 0;
uint32_t s_compare = 0; //globol variables to count move and compare
//find proper gap index

void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t temp = 0;
    for (int g = 0; g < GAPS; g++) { //for gap in gaps
        for (uint32_t i = gaps[g]; i < n; i++) { //for i in range (gap, len(arr))
            uint32_t j = i;
            s_move++;
            temp = A[i];
            while (j >= gaps[g] && ++s_compare
                   && temp < A[j - gaps[g]]) { //while j>= gap and temp<arr[i-gap]
                s_move++;
                A[j] = A[j - gaps[g]];
                j -= gaps[g];
            }
            s_move++;
            A[j] = temp;
        }
    }
}
//followed the python pesudocode from pdf

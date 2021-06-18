#include "bm.h"

#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

//follow function ref@asgn5.pdf section BitMatrix.

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix)); //create pointer bm
    if (bm) { // if allocated memory correctly
        bm->rows = rows;
        bm->cols = cols;
        bm->vector = bv_create(rows * cols); //initial variables
        if (!bm->vector) {
            free(bm->vector);
            free(bm);
            bm = NULL;
        }
    } else { //if failed, free memory
        free(bm);
        bm = NULL;
    }
    return bm;
}

void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&((*m)->vector)); //delete the content in vector
        free((*m)->vector); //free vector memory
    }
    free(*m); //free pointer
    *m = NULL; //set pointer to null
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
} //return rows

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
} //return cols

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * m->cols + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = bm_create(1, length);
    //check whether sufficient memory can be allocated
    if (bm) {
        for (uint32_t i = 0; i < length; i++) {
            bv_xor_bit(bm->vector, i, (byte & (1 << i)) == 0 ? 0 : 1);
        }
    }
    return bm;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t u8 = 0;
    uint8_t set_bit = 1;
    for (uint32_t i = 0; i < 8; i++) { //loop for 8 bits
        if (bv_get_bit(m->vector, i)) { //if 1, set bit
            u8 |= set_bit;
        }
        set_bit <<= 1;
    }
    return u8;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *C = bm_create(A->rows, B->cols);
    uint32_t temp = 0;
    if (C) {
        temp = 0;
        //matrix multiply
        for (uint32_t i = 0; i < A->rows; i++) {
            for (uint32_t j = 0; j < B->cols; j++) {
                for (uint32_t k = 0; k < A->cols; k++) {
                    temp += bm_get_bit(A, i, k) * bm_get_bit(B, k, j);
                }
                temp %= 2;
                if (temp) {
                    bm_set_bit(C, i, j);
                }
                temp = 0;
            }
        }
    }
    return C;
}

void bm_print(BitMatrix *m) {
    printf("====BitMatrix====\n");
    printf("rows:%u\n", m->rows);
    printf("cols:%u\n", m->cols);
    bv_print(m->vector);
    printf("\n=================\n");
}

//also inspired by sahiti section

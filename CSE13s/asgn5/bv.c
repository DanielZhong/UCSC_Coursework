#include "bv.h"

#include <stdio.h>
#include <stdlib.h> //For malloc()

struct BitVector {
    uint32_t length; // Length in bits .
    uint8_t *vector; // Array of bytes .
};

BitVector *bv_create(uint32_t length) {
    //alloc memory for bitvector
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        //alloc memory for vector to store the bit
        bv->vector = (uint8_t *) calloc((length - 1) / 8 + 1, sizeof(uint8_t));
        bv->length = length;
        //if failed alloc
        if (!bv->vector) {
            free(bv->vector);
            free(bv);
            bv = NULL;
        }
    } else {
        //if failed alloc
        free(bv);
        bv = NULL;
    }
    return bv;
}

void bv_delete(BitVector **v) {
    //free (*v)->vector first
    if (*v && (*v)->vector) {
        free((*v)->vector);
    }
    free(*v);
    *v = NULL;
}

uint32_t bv_length(BitVector *v) {
    //return the length of bitvector
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    //ref question@622: If the index i is greater than the length of the bit vector itself (in bits), then you can’t set the i-th bit.
    if (i > v->length) {
        return;
    }
    //make i-th bit a 1
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t set_on = 1 << position;
    v->vector[location] |= set_on;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    if (i > v->length) {
        return;
    }
    //make i-th bit a 0
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t set_off = 1 << position;
    v->vector[location] &= ~set_off;
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    if (i > v->length) {
        return;
    }
    //make i-th bit the result of itself XOR bit
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t set_xor = (1 * bit) << position;
    v->vector[location] ^= set_xor;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    //get i-th bit
    uint32_t location = i / 8;
    uint32_t position = i % 8;
    uint8_t get_bit = 1 << position;
    return (v->vector[location] & get_bit) ? 1 : 0;
}

void bv_print(BitVector *v) {
    //for debug use
    printf("====BitVector====\n");
    printf("length:%u\n", v->length);

    printf("bits:|");
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%u", bv_get_bit(v, i));
        if (i != 0 && !(i % 8)) {
            printf("|");
        }
    }
    printf("\n=================\n");
}

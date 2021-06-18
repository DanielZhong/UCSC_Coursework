#include "code.h"

#include <stdio.h>

Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
} //initial code and return

uint32_t code_size(Code *c) {
    return c->top;
} //return top(size)

bool code_empty(Code *c) {
    return c->top == 0 ? true : false;
} //if size == 0, return true, otherwise false

bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE ? true : false;
} //check if top == maximium size

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    uint32_t location = c->top / 8;
    uint32_t position = c->top % 8;
    bit <<= position;
    c->bits[location] |= bit; //use or bit to set  bit
    c->top++; //update the size
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top--; //update size
    uint32_t location = c->top / 8;
    uint32_t position = c->top % 8;
    *bit = c->bits[location] & (1 << position);
    //clear the top-th bit
    c->bits[location] &= (~(1 << position));
    return true;
}

void code_print(Code *c) {

    fprintf(stderr, "\n----Code----\n");
    fprintf(stderr, "top:%u\n", c->top);
    fprintf(stderr, "bits:0x%x", c->bits[0]);

    fprintf(stderr, "\n------------\n");
}

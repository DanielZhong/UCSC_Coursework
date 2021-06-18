#include "hamming.h"

#include "bm.h"
#include "danielz.h"

#include <stdio.h>

int32_t lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
    HAM_ERR, 1, 0, HAM_ERR };

uint32_t uncorrected_byte = 0;
uint32_t corrected_byte = 0;

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    //store hamming code
    uint8_t code = 0;
    //create matrix form msg
    BitMatrix *msg_m = bm_from_data(msg, 4);
    //multiply msg and G and return the code matrix
    BitMatrix *code_m = bm_multiply(msg_m, G);
    //make code matrix a uint8_t
    code = bm_to_data(code_m);
    //free the memory
    bm_delete(&msg_m);
    bm_delete(&code_m);
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    //init the return value
    HAM_STATUS status = HAM_OK;
    //prepare the matrix to multiply
    BitMatrix *code_m = bm_from_data(code, 8);
    BitMatrix *encode_m = bm_multiply(code_m, Ht);
    uint8_t e = bm_to_data(encode_m);
    //if e != 0 means there must have error
    if (e != 0) {
        //compare the error syndrome with each row in Ht
        if (e != 0 && lookup[e] != HAM_ERR) {
            corrected_byte++;
            status = HAM_CORRECT;
            //flip i_th bit
            if (bm_get_bit(code_m, 0, lookup[e])) {
                bm_clr_bit(encode_m, 0, lookup[e]);
            } else {
                bm_set_bit(encode_m, 0, lookup[e]);
            }
        } else { //there have uncorrectable error(s)
            status = HAM_ERR;
            uncorrected_byte++;
        }
    }
    //retrive the msg from hamming code
    *msg = lower_nibble(bm_to_data(code_m));
    bm_delete(&code_m);
    bm_delete(&encode_m);
    return status;
}

#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

//ref@pdf
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};
//ref@pdf
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d; //salts
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter);
    }
    free(*bf);
    bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t l = bv_length(bf->filter);
    //set 3 salts into bloomfilter indices
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % l);
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % l);
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % l);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    //get 3 salts
    uint32_t a = hash(bf->primary, oldspeak);
    uint32_t b = hash(bf->secondary, oldspeak);
    uint32_t c = hash(bf->tertiary, oldspeak);
    uint32_t l = bv_length(bf->filter);

    //if 3 bits are set, then return true
    if (bv_get_bit(bf->filter, a % l) && bv_get_bit(bf->filter, b % l)
        && bv_get_bit(bf->filter, c % l)) {
        return true;
    }
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t cnt = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            cnt++;
        }
    }
    return cnt;
}

void bf_print(BloomFilter *bf) {
    printf("\n====BLOOMFILTER====\n");
    bv_print(bf->filter);
    printf("\n===================\n");
}

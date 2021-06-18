#include "ht.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

//ref@pdf
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    } //initial variables
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < ht_size(*ht); i++) {
            ll_delete(&((*ht)->lists[i])); //free linklist and nodes inside hash index
        }
        free((*ht)->lists);
    }
    free(*ht);
    *ht = NULL;
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size; //return size
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t ht_idx = hash(ht->salt, oldspeak);
    //look up the linklist for oldspeak
    return ll_lookup(ht->lists[ht_idx % ht_size(ht)], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t ht_idx = hash(ht->salt, oldspeak);
    uint32_t size = ht_size(ht);
    //If the linked list that should be inserted into hasn’t been initialized yet, create it first before inserting the oldspeak and newspeak
    if (!ht->lists[(ht_idx % size)]) {
        ht->lists[(ht_idx % size)] = ll_create(ht->mtf);
        ll_insert(ht->lists[(ht_idx % size)], oldspeak, newspeak);
    } else {
        ll_insert(ht->lists[(ht_idx % size)], oldspeak, newspeak);
    }
}

uint32_t ht_count(HashTable *ht) {
    uint32_t cnt = 0;
    for (uint32_t i = 0; i < ht->size; i++) { // loop size times
        if (ht->lists[i]) {
            cnt++;
        }
    }
    return cnt;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        ll_print(ht->lists[i]); //for each index of hashtable print each linklist element
    }
}

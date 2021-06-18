#include "bf.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h> //strtoul()
#include <unistd.h> //getopt()

#define OPTIONS     "ht:f:ms"
#define INPUT_BASE  10
#define WORD        "([a-zA-Z0-9]((-|'|_)[a-zA-Z0-9])?)+"
#define WORD_MAX_SZ 1024

void help(char *name);

int main(int argc, char *argv[]) {
    //gathering the input command
    int opt = 0;
    uint32_t ht_sz = 10000;
    uint32_t bf_sz = 1 << 20;
    bool mtf = false;
    bool statistics = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help(argv[0]);
            exit(0);
            break;
        case 't': ht_sz = strtoul(optarg, NULL, INPUT_BASE); break;
        case 'f': bf_sz = strtoul(optarg, NULL, INPUT_BASE); break;
        case 'm': mtf = true; break;
        case 's': statistics = true; break;
        default:
            help(argv[0]);
            exit(0);
            break;
        }
    }

    //create bloom filter and hash table
    BloomFilter *b = bf_create(bf_sz);
    HashTable *h = ht_create(ht_sz, mtf);

    //read in oldspeak words from badspeak.txt and insert each word to bf and ht
    FILE *oldspeak = fopen("badspeak.txt", "r");
    char s[WORD_MAX_SZ];
    while (fscanf(oldspeak, "%s", s) != -1) {
        bf_insert(b, s);
        ht_insert(h, s, NULL);
    }

    //read in newspeak word from newspeak.txt and insert each word to bf and ht
    FILE *newspeak = fopen("newspeak.txt", "r");
    char o[WORD_MAX_SZ];
    char n[WORD_MAX_SZ];
    while (fscanf(newspeak, "%s %s\n", o, n) != -1) {
        bf_insert(b, o);
        ht_insert(h, o, n);
    }

    //limit input, ref to pdf
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        perror("regcomp");
        exit(1);
    }

    LinkedList *badword = ll_create(mtf);
    LinkedList *translation = ll_create(mtf);
    char *word = NULL;
    //if word passed all reqiurment(regex)
    while ((word = next_word(stdin, &re)) != NULL) {
        int i = 0;
        while (1) {
            if (word[i] == '\0') {
                break;
            }
            if (word[i] >= 65 && word[i] <= 90) { //change A-Z to a-z
                word[i] += 32;
            }
            i++;
        }

        if (bf_probe(b, word) == true) { //check bloom filter
            Node *word_node = ht_lookup(h, word);
            if (word_node != NULL) { //check hash table
                if (word_node->newspeak == NULL) { //check if oldspeak
                    ll_insert(badword, word, NULL);
                } else {
                    ll_insert(translation, word,
                        word_node->newspeak); //if newspeak, also print translation
                }
            }
        }
    }

    //Enabling statistics
    if (!statistics) {
        if (ll_length(translation) != 0 && ll_length(badword) != 0) {
            printf("%s", mixspeak_message);
            ll_print(badword);
            ll_print(translation);
        } else if (ll_length(badword) != 0 && ll_length(translation) == 0) {
            printf("%s", badspeak_message);
            ll_print(badword);
        } else if (ll_length(translation) == 0 && ll_length(badword) != 0) {
            printf("%s", goodspeak_message);
            ll_print(translation);
        } // check if it's bad word or new word to print the correct message
    } else {
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %.6lf\n", 1.0 * links / seeks);
        printf("Hash table load: %.6lf%% \n", 100 * (1.0 * ht_count(h) / ht_size(h)));
        printf("Bloom filter load: %.6lf%% \n", 100 * (1.0 * bf_count(b) / bf_size(b)));
    }

    bf_delete(&b);
    ht_delete(&h);
    ll_delete(&badword);
    ll_delete(&translation);
    clear_words();
    regfree(&re);
    fclose(oldspeak);
    fclose(newspeak);
    return 0;
}

//help message
void help(char *name) {
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  %s [-hsm] [-t size] [-f size]\n", name);
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h           Program usage and help.\n");
    printf("  -s           Print program statistics.\n");
    printf("  -m           Enable move-to-front rule.\n");
    printf("  -t size      Specify hash table size (default: 10000).\n");
    printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
}

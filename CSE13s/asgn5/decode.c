#include "bm.h"
#include "danielz.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

#define G_ROWS 8
#define G_COLS 4
uint8_t m_Ht[G_ROWS][G_COLS] = {
    { 0, 1, 1, 1 },
    { 1, 0, 1, 1 },
    { 1, 1, 0, 1 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
};

extern uint32_t uncorrected_byte;
extern uint32_t corrected_byte;

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infp = stdin;
    FILE *outfp = stdout;
    bool verbose = false;
    //Parse the command-line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_decode();
            exit(0);
            break;
        case 'i':
            if ((infp = fopen(optarg, "rb")) == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                exit(1);
            }
            break;
        case 'v': verbose = true; break;
        case 'o':
            if ((outfp = fopen(optarg, "wb")) == NULL) {
                fprintf(stderr, "Error: failed to open outfile.\n");
                exit(1);
            }
            break;
        }
    }
    //ref@asgn5.pdf : handdle file permmision
    struct stat statbuf;
    fstat(fileno(infp), &statbuf);
    fchmod(fileno(outfp), statbuf.st_mode);

    //Initialize the generator matrix Ht using bm_create().
    BitMatrix *Ht = bm_create(G_ROWS, G_COLS);
    for (uint32_t i = 0; i < G_ROWS; i++) {
        for (uint32_t j = 0; j < G_COLS; j++) {
            if (m_Ht[i][j]) {
                bm_set_bit(Ht, i, j);
            }
        }
    }
    uint32_t total_bytes = 0;
    //Read two bytes from the specified file stream or stdin with fgetc().
    uint8_t code1 = fgetc(infp);
    uint8_t code2 = fgetc(infp);
    uint8_t lower_nibble = 0;
    uint8_t upper_nibble = 0;
    uint8_t msg = 0;
    while (!feof(infp)) {
        //count how many byte this program process
        total_bytes += 2;
        ham_decode(Ht, code1, &lower_nibble);
        ham_decode(Ht, code2, &upper_nibble);
        msg = pack_byte(upper_nibble, lower_nibble);
        //Write the reconstructed byte with fputc().
        fputc(msg, outfp);
        code1 = fgetc(infp);
        code2 = fgetc(infp);
    }

    //prevent memory leak
    bm_delete(&Ht);
    fclose(infp);
    fclose(outfp);

    //print the statistics
    if (verbose) {
        fprintf(stderr, "Total bytes processed: %u\n", total_bytes);
        fprintf(stderr, "Uncorrected errors: %u\n", uncorrected_byte);
        fprintf(stderr, "Corrected errors: %u\n", corrected_byte);
        fprintf(stderr, "Error rate: %f\n", 1.0 * uncorrected_byte / total_bytes);
    }
    return 0;
}

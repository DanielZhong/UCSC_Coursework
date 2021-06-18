#include "bm.h"
#include "danielz.h"
#include "hamming.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:"

#define G_ROWS 4
#define G_COLS 8
uint8_t m_G[G_ROWS][G_COLS] = {
    { 1, 0, 0, 0, 0, 1, 1, 1 },
    { 0, 1, 0, 0, 1, 0, 1, 1 },
    { 0, 0, 1, 0, 1, 1, 0, 1 },
    { 0, 0, 0, 1, 1, 1, 1, 0 },
};

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infp = stdin;
    FILE *outfp = stdout;

    //Parse the command-line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_encode();
            exit(0);
            break;
        case 'i':
            if ((infp = fopen(optarg, "rb")) == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                exit(1);
            }
            break;
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

    //Initialize the generator matrix G using bm_create().
    BitMatrix *G = bm_create(G_ROWS, G_COLS);
    for (uint32_t i = 0; i < G_ROWS; i++) {
        for (uint32_t j = 0; j < G_COLS; j++) {
            if (m_G[i][j]) {
                bm_set_bit(G, i, j);
            }
        }
    }

    //Read a byte from the specified file stream or stdin with fgetc().
    uint8_t msg = 0;
    uint8_t code = 0;
    msg = fgetc(infp);
    while (!feof(infp)) {
        //Generate the Hamming(8,4) codes for both the upper and lower nibble with ham_encode()
        code = ham_encode(G, lower_nibble(msg));
        fputc(code, outfp);
        code = ham_encode(G, upper_nibble(msg));
        fputc(code, outfp);
        msg = fgetc(infp);
    }
    //close file pointer and free allocated memory
    bm_delete(&G);
    fclose(infp);
    fclose(outfp);

    return 0;
}

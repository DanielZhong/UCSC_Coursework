#include "danielz.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

extern uint16_t unique_symbol;

int main(int argc, char *argv[]) {
    int opt = 0;
    int infile = 0;
    int outfile = 1;

    bool verbose = false;

    //0. Parse the command-line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_encode();
            exit(0);
            break;
        case 'i':
            if ((infile = open(optarg, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "Error: failed to open infile.\n");
                exit(1);
            }
            break;
        case 'o':
            if ((outfile = open(optarg, O_WRONLY, 0)) == -1) {
                fprintf(stderr, "Error: failed to open outfile.\n");
                exit(1);
            }
            break;
        case 'v': verbose = true; break;
        }
    }

    //1. Read through infile to construct a histogram
    uint64_t hist[ALPHABET];
    memset(hist, 0, sizeof(hist));
    uint8_t c = '\0';
    while (read_bytes(infile, &c, 1) > 0) {
        hist[c]++;
    } //read each character in the infile, and hist++ to record frequency

    //2. Increment the count of element 0 and element 255 by one in the histogram
    hist[0]++;
    hist[255]++;

    Node *root = build_tree(hist);

    //4. Construct a code table by traversing the Huffman tree This will be done using build_codes().
    Code table[ALPHABET];
    build_codes(root, table);

    //5. Construct a header.
    struct stat statbuf;
    Header h;
    h.magic = MAGIC;
    fstat(infile, &statbuf);
    h.permissions = statbuf.st_mode;
    h.tree_size = 3 * unique_symbol - 1;
    h.file_size = statbuf.st_size;
    fchmod(outfile, statbuf.st_mode);

    //6. Write the constructed header to outfile
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));

    //7. Perform a post-order traversal of the Huffman tree to write the tree to the outfile
    write_tree(outfile, root);

    //8. Starting at the beginning of infile, write the corresponding code for each symbol to outfile with write_code(). When finished with all the symbols, make sure to flush any remaining buffered codes with flush_codes().
    lseek(infile, 0, 0);
    while (read_bytes(infile, &c, 1) > 0) {
        write_code(outfile, &table[c]);
    }
    flush_codes(outfile);
    if (verbose) {
        fprintf(stderr, "\nUncompressed file size:%lu\n", h.file_size);
        fprintf(stderr, "Compressed file size:%lu\n", bytes_written);
        fprintf(stderr, "Space saving:%.2f%%\n", 100 * (1 - (1.0 * bytes_written / h.file_size)));
    }

    //9. Close infile and outfile.
    delete_tree(&root);

    close(infile);
    close(outfile);
    return 0;
}

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

int main(int argc, char *argv[]) {

    int opt = 0;
    int infile = 0; //stdin
    int outfile = 1; //stdout
    bool verbose = false;

    //0. Parse the command-line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_decode();
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

    //1. Read in the header from infile and verify the magic number.
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    if (h.magic != MAGIC) {
        fprintf(stderr, "magic number does not match!\n");
        exit(1);
    }

    //2. The permissions field in the header indicates the permissions that outfile should be set to
    struct stat statbuf;
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);

    //3. Read the dumped tree from infile into an array that is tree_size bytes long
    uint8_t tree[h.tree_size];
    read_bytes(infile, tree, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, tree);

    //4. Read infile one bit at a time using read_bit(). You will be traversing down the tree one link at a time for each bit that is read.
    Node *n = root;
    uint64_t symbol_number = 0;
    uint8_t bit = '0';

    //4c. Repeat until the number of decoded symbols matches the original file size, which is given by the file_size field in the header that was read from infile
    uint8_t text[BLOCK]; //decrease the write opreation
    int text_idx = 0;

    //use read_bit find node and use write_code write symbol
    while (symbol_number < h.file_size) {
        read_bit(infile, &bit);
        if (bit) {
            n = n->right;
            //4b. If you find yourself at a leaf node, then write the leaf node’s symbol to outfile.
        } else {
            n = n->left;
        }
        if (n->left == NULL && n->right == NULL) {
            symbol_number++;
            text[text_idx++] = n->symbol;
            n = root;
            if (text_idx == BLOCK) {
                write_bytes(outfile, text, BLOCK);
                text_idx = 0;
            }
        }
    }
    write_bytes(outfile, text, text_idx); //flush

    if (verbose) {
        fprintf(stderr, "Compressed file size:%lu bytes\n", bytes_read);
        fprintf(stderr, "Dempressed file size:%lu bytes\n", bytes_written);
        fprintf(stderr, "Space saving:%.2f%%\n", 100 * (1 - (1.0 * bytes_read / bytes_written)));
    }

    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}

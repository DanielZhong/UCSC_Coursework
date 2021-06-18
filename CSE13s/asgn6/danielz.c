#include "danielz.h"

#include "io.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void post_order_traverse(Node *root, Code *c, Code table[static ALPHABET]) {
    if (root == NULL) {
        return;
    }
    //4b. If the current node is a leaf, the current code c represents the path to the node
    if (root->left == NULL && root->right == NULL) {
        table[root->symbol] = *c;
        return;
    }
    //4c. Else, the current node must be an interior node. Push a 0 to c and recurse down the left link
    code_push_bit(c, 0);
    post_order_traverse(root->left, c, table);
    //4d. After you return from the left link, pop a bit from c, push a 1 to c and recurse down the right link.
    uint8_t poped_bit = 0;
    code_pop_bit(c, &poped_bit);
    code_push_bit(c, 1);
    post_order_traverse(root->right, c, table);
    //4d. Remember to pop a bit from c when you return from the right link.
    code_pop_bit(c, &poped_bit);
}

void write_tree(int outfile, Node *root) {
    if (root == NULL) {
        return;
    }
    uint8_t leaf = '\0';
    //write an ‘L’ followed by the byte of the symbol for each leaf
    if (root->left == NULL && root->right == NULL) {
        leaf = 'L';
        write_bytes(outfile, &leaf, sizeof(uint8_t));
        leaf = root->symbol;
        write_bytes(outfile, &leaf, sizeof(uint8_t));
        return;
    }
    write_tree(outfile, root->left);
    write_tree(outfile, root->right);

    leaf = 'I';
    write_bytes(outfile, &leaf, sizeof(uint8_t));
}

void help_encode(void) {
    printf("SYNOPSIS\n"
           "  A Huffman encoder.\n"
           "  Compresses a file using the Huffman coding algorithm.\n"
           "\n"
           "USAGE\n"
           "  ./encode [-h] [-i infile] [-o outfile]\n"
           "\n"
           "OPTIONS\n"
           "  -h             Program usage and help.\n"
           "  -v             Print compression statistics.\n"
           "  -i infile      Input file to compress.\n"
           "  -o outfile     Output of compressed data.\n");
}

void help_decode(void) {
    printf("SYNOPSIS\n"
           "  A Huffman decoder.\n"
           "  Decompresses a file using the Huffman coding algorithm.\n"
           "\n"
           "USAGE\n"
           "  ./decode [-h] [-i infile] [-o outfile]\n"
           "\n"
           "OPTIONS\n"
           "  -h             Program usage and help.\n"
           "  -v             Print compression statistics.\n"
           "  -i infile      Input file to decompress.\n"
           "  -o outfile     Output of decompressed data.\n");
}

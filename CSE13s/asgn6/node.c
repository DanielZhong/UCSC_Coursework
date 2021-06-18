#include "node.h"

#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

void node_delete(Node **n) {
    if (*n != NULL) {
        if ((*n)->left != NULL) {
            node_delete(&(*n)->left);
        }
        if ((*n)->right != NULL) {
            node_delete(&(*n)->right);
        }
        free(*n);
        *n = NULL;
    }
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

void node_print(Node *n) {
    printf("----Node----\n");
    printf("frequency:%lu", n->frequency);
    printf("symbol:%c", n->symbol);
    printf("-------------\n");
}

#include "huffman.h"

#include "danielz.h"
#include "defines.h"
#include "pq.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

uint16_t unique_symbol = 0;
//Constructs a Huffman tree given a computed histogram

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //3. Construct the Huffman tree using a priority queue. This will be done using build_tree().
    //3a. Create a priority queue
    PriorityQueue *pq = pq_create(ALPHABET);
    //3a. For each symbol histogram where its frequency is greater than 0,create a corresponding Node and insert it into the priority queue.
    Node *n = NULL;
    uint8_t c = 0;
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[c] > 0) {
            n = node_create(c, hist[c]);
            enqueue(pq, n);
            unique_symbol++;
        }
        c++;
    }
    //3b. While there are two or more nodes in the priority queue
    while (pq_size(pq) >= 2) {
        //3b. dequeue two node
        Node *fist_node = NULL, *second_node = NULL;
        dequeue(pq, &fist_node);
        dequeue(pq, &second_node);
        //3b. The first dequeued node will be the left child node The second dequeued node will be the right child node
        Node *parent = node_join(fist_node, second_node);
        //3b. enqueue the joined parent node
        enqueue(pq, parent);
    }
    //3c. Eventually, there will only be one node left in the priority queue. This node is the root of the constructed Huffman tree.
    Node *root;
    dequeue(pq, &root);
    pq_delete(&pq);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //Populates a code table, building the code for each symbols in the Huffman tree
    Code c = code_init();
    //4a. Starting at the root of the Huffman tree, perform a post-order traversal.
    post_order_traverse(root, &c, table);
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    //Reconstructs a Huffman tree given its post-order tree dump stored in the array tree_dump
    Stack *s = stack_create(MAX_TREE_SIZE);
    //3a. The array containing the dumped tree will be referred to as tree_dump

    //3b. Iterate over the contents tree_dump from 0 to nbytes.
    for (uint16_t i = 0; i < nbytes; i++) {
        //If the element of the array is an ‘L’,then the next element will be the symbol for the leaf node.
        if (tree[i] == 'L') {
            //Use that symbol to create a new node with node_create(). Push the created node onto the stack.
            i++;
            stack_push(s, node_create(tree[i], 0));
        } else if (tree[i] == 'I') {
            Node *right;
            stack_pop(s, &right);
            Node *left;
            stack_pop(s, &left);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    //3e. There will be one node left in the stack after you finish iterating over the contents tree_dump. This node is the root of the Huffman tree.
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {
    //This will require a post-order traversal of the tree to free all the nodes
    node_delete(root);
}

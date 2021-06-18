#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strdup(s) strcpy(malloc(strlen(s) + 1), s) //mimic strdup

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        if (oldspeak == NULL) {
            n->oldspeak = NULL; //if oldspeak == null, then set it to null
        } else {
            n->oldspeak = strdup(oldspeak); //strdup oldspeak
        }

        if (newspeak == NULL) {
            n->newspeak = NULL; //if newspeak == null, then set it to null
        } else {
            n->newspeak = strdup(newspeak); //strdup oldspeak
        }
        n->next = NULL;
        n->prev = NULL; //next and prev initial == NULL
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        free((*n)->newspeak); //free oldspeak and newspeak inside node
    }
    free(*n);
    *n = NULL;
    return;
}

void node_print(Node *n) {
    if (n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    } else {
        printf("%s -> %s\n", n->oldspeak, n->newspeak); //if not oldspeak, then print newspeak
    }
}

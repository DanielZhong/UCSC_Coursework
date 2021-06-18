#include "ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks = 0;
uint64_t links = 0; // -s statistics

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->head = node_create("", "");
        ll->tail = node_create("", "");
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->mtf = mtf; //initial length, head, tail, mtf, next, and prev
    }
    return ll;
}

void ll_delete(LinkedList **ll) {
    Node *x;
    if (*ll) {
        while ((*ll)->head != NULL) {
            x = (*ll)->head->next;
            node_delete(&((*ll)->head));
            (*ll)->head = x;
        }
    }
    free(*ll);
    *ll = NULL;
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length; //return length
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks++;
    Node *v;
    for (v = ll->head; v != ll->tail; v = v->next) {
        if (v != ll->head) {
            links++;
        }
        if (!strcmp(oldspeak, v->oldspeak)) {
            //check whether move-to-front option was specified
            if (ll->mtf) {
                v->prev->next = v->next;
                v->next->prev
                    = v->prev; //remove the original node location, reset original location's prev and next
                v->next = ll->head->next;
                v->prev = ll->head;
                ll->head->next->prev = v;
                ll->head->next = v; // put this node to the front
            }
            return v; //return the node, if founded
        }
    }
    return NULL; //if can't find it, return NUll
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak)
        == NULL) { //if node == null, meaning no word in the linklist, insert a new one
        Node *n = node_create(oldspeak, newspeak);
        n->prev = ll->head; //create new node after linklist head(begining of the linklist)
        n->next = ll->head->next;
        ll->head->next->prev = n;
        ll->head->next = n;
        ll->length += 1; //update length
    }
}

void ll_print(LinkedList *ll) {
    if (ll) {
        Node *n;
        n = (ll)->head->next;
        while (n->next != NULL) { //if not end of the linklist, node print
            node_print(n);
            n = n->next;
        }
    }
    return;
}

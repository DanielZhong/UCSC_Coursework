#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

// The lower the frequency of a node, the higher its priority.
// 1) using a min heap to serve as the priority queue. [-]
// 2) mimicking an insertion sort when enqueuing a node.[+]
struct PriorityQueue {
    uint32_t head;
    uint32_t tail;

    uint32_t size; // The number of elements in the queue.
    uint32_t capacity; // Capacity of the queue.
    Node **items; // Holds the items in decending order from head to tail
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->head = 0;
    pq->tail = 0;
    pq->size = 0;
    pq->capacity = capacity;
    pq->items = calloc(capacity, sizeof(Node *));
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (*q != NULL) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
}

bool pq_empty(PriorityQueue *q) {
    return q->size == 0 ? true : false;
}

bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity ? true : false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

//mimicking an insertion sort when enqueuing a node
//make sure the min item at the head of queue

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }

    //finding the correct position for the node
    uint32_t i = 0;
    for (i = q->head; i % q->capacity != q->tail; i++) {
        if (q->items[i % q->capacity]->frequency >= n->frequency) {
            break;
        }
    }
    i %= q->capacity;
    //shift everything from i to tail back
    uint32_t j = q->tail;
    while (j % q->capacity != i) {
        j == 0 ? j = q->capacity - 1 : j--;
        q->items[(j + 1) % q->capacity] = q->items[j % q->capacity];
    }

    //add Node to queue at index i
    q->items[i] = n;
    q->tail++;
    q->tail %= q->capacity;
    q->size++;

    return true;
}

//delete items from head.
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->items[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return true;
}

void pq_print(PriorityQueue *q) {

    printf("\n----Queue----\n");
    if (q == NULL) {
        printf("NULL\n");
        return;
    }
    printf("capacity:%u\n", q->capacity);
    printf("head:%u\n", q->head);
    printf("tail:%u\n", q->tail);
    uint32_t i = 0;
    for (i = q->head; (i % q->capacity) != q->tail; i++) {
        printf("frequency[%u]=%lu ", i % q->capacity, (q->items[i % q->capacity])->frequency);
    }
    printf("\n-------------\n");
}

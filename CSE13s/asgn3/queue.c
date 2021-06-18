#include "queue.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    uint32_t head; // Index of the head of the queue.
    uint32_t tail; // Index of the tail of the queue.
    uint32_t size; // The number of elements in the queue.
    uint32_t capacity; // Capacity of the queue.
    int64_t *items; // Holds the items.
};

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) { // if sucess alloc memory
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) { //prevent memory leak
            free(q);
            q = NULL;
        }
    }
    return q;
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) { //remove the item in each queue slot first
        free((*q)->items); //remove queue allocated memory
        free(*q); //free pointer
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    return q->size == 0 ? true : false;
}

bool queue_full(Queue *q) {
    return q->size == q->capacity ? true : false;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) {
    bool test = true;
    if (queue_full(q)) {
        test = false;
    } else {
        //add head item in queue
        q->items[q->head] = x;
        q->size++;
        q->head++;
        q->head %= q->capacity;
    }
    return test;
}

bool dequeue(Queue *q, int64_t *x) {
    //save the return value
    bool test = true;
    if (queue_empty(q)) {
        test = false;
    } else {
        //delete tail item and pass it to *x
        *x = q->items[q->tail];
        q->size--;
        q->tail++;
        q->tail %= q->capacity;
    }
    return test;
}

void queue_print(Queue *q) {
    printf("====Queue====\n");
    printf("head:%u\n", q->head);
    printf("tail:%u\n", q->tail);
    printf("size:%u\n", q->size);
    printf("capacity:%u\n", q->capacity);
    printf("items:|");
    for (uint32_t i = 0; i < q->size; i++) {
        printf("%ld|", q->items[(i + q->tail) % q->capacity]);
    }
    printf("\n=============\n");
}

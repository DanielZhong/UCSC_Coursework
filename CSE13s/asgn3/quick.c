#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>

uint32_t s_size = 0;
uint32_t q_size = 0;
uint32_t q_move = 0;
uint32_t q_compare = 0;

void max_update(uint32_t *max, uint32_t current) {
    if (current > *max) {
        *max = current;
    }
}

void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
} //swap two value in the sort

//followed by pdf python pesudocode
int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + (hi - lo) / 2]; // choose the middle emelent in A[lo,hi] as pivot
    int64_t i = lo - 1;
    int64_t j = hi + 1;

    while (i < j) {
        do {
            i++;
            q_compare++;
        } while (A[i] < pivot);

        do {
            j--;
            q_compare++;
        } while (A[j] > pivot);

        if (i < j) {
            q_move += 3;
            swap(&A[i], &A[j]);
        }
    }
    return j;
}

//followed by pdf python pesudocode
void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t p = 0;
    int64_t lo = 0, hi = n - 1;
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    s_size = 0;
    max_update(&s_size, stack_size(s));
    while (stack_size(s) != 0) {
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
            max_update(&s_size, stack_size(s));
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
            max_update(&s_size, stack_size(s));
        }
    }
    //free the stack
    stack_delete(&s);
    assert(s == NULL);
}

//followed by pdf python pesudocode
void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t p = 0;
    int64_t lo = 0, hi = n - 1;

    Queue *q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    q_size = 0;
    max_update(&q_size, queue_size(q));
    while (queue_size(q) != 0) {
        dequeue(q, &lo);
        dequeue(q, &hi);
        p = partition(A, lo, hi);
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
            max_update(&q_size, queue_size(q));
        }
        if (hi > p + 1) {
            enqueue(q, p + 1);
            enqueue(q, hi);
            max_update(&q_size, queue_size(q));
        }
    }
    //free the queue
    queue_delete(&q);
    assert(q == NULL);
}

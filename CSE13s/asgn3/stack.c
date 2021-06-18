#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> //For malloc() and For calloc()

struct Stack {
    uint32_t top; // Index of the next empty slot.
    uint32_t capacity; // Number of items that can be pushed.
    int64_t *items; // Array of items , each with type int64_t.
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocated memory for stack
    // if success alloc
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        // if fail alloc
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}
//cited from pdf

void stack_delete(Stack **s) {
    if (*s && (*s)->items) { //free stack item first
        free((*s)->items); //free stack allocated memory
        free(*s); //free pointer
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0 ? true : false; //check if the stack is empty?
}

bool stack_full(Stack *s) {
    return s->top == s->capacity ? true : false; //check if stack is full?
}

uint32_t stack_size(Stack *s) { //return top
    return s->top;
}

bool stack_push(Stack *s, int64_t x) {
    bool test = true;
    if (stack_full(s)) {
        test = false; //if stack is full, then return false
    } else {
        s->items[s->top++] = x;
    } //if stack not empty, return true, push x and add top
    return test;
}

bool stack_pop(Stack *s, int64_t *x) {
    bool test = true;
    if (stack_empty(s)) {
        test = false; //if stack is empty, then return false
    } else {
        s->top--;
        *x = s->items[s->top];
    } //if stack not empty, return true, pop x and minus top
    return test;
}

void stack_print(Stack *s) {
    printf("====Stack====\n");
    printf("top:%u\n", s->top);
    printf("capacity:%u\n", s->capacity);
    printf("items:|");
    for (uint32_t i = 0; i < s->top; i++) {
        printf("%ld|", s->items[i]);
    }
    printf("\n=============\n");
}

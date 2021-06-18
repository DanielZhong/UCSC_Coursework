#include "stack.h"

#include <stdio.h>
#include <stdlib.h> //For malloc() and For calloc()

struct Stack {
    uint32_t top; // Index of the next empty slot.
    uint32_t capacity; // Number of items that can be pushed.
    uint32_t *items; // Array of items , each with type int32_t.
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    // if success alloc
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        // if fail alloc
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) { //if not empty in the items
        free((*s)->items); //free evertying in the matrix first
        free(*s); //free pointer
        *s = NULL; //set pointer to null
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0 ? true : false;
} //if top equal 0, return true, else return false

bool stack_full(Stack *s) {
    return s->top == s->capacity ? true : false;
} //check if top reach max capacity

uint32_t stack_size(Stack *s) {
    return s->top;
} //return top

bool stack_push(Stack *s, uint32_t x) {
    bool flag = true;
    if (stack_full(s)) {
        flag = false; //if the stack is full, return false
    } else {
        s->items[s->top++] = x; //else, push stack
    }
    return flag;
}

//querying a stack about the element at the top of the stack
bool stack_peek(Stack *s, uint32_t *x) {
    bool flag = false;
    if (!stack_empty(s)) { //if stack not empty
        *x = s->items[s->top - 1];
        flag = true;
    }
    return flag;
}

bool stack_pop(Stack *s, uint32_t *x) {
    bool flag = false;
    if (!stack_empty(s)) { //if stack not empty
        s->top--; //update top
        *x = s->items[s->top];
        flag = true;
    }
    return flag;
}

void stack_copy(Stack *dst, Stack *src) {
    //Assuming that the destination stack dst is properly initialized
    dst->top = src->top;
    dst->capacity = src->capacity;
    //copy items from src to dst
    for (uint32_t i = 0; i < src->capacity; i++) {
        dst->items[i] = src->items[i];
    }
    return;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}

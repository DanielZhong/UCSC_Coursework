#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    s->capacity = capacity;
    s->items = calloc(capacity, sizeof(Node *));
    return s;
}

void stack_delete(Stack **s) {
    if (*s) {
        free((*s)->items);
    }
    free(*s);
    *s = NULL;
}

bool stack_empty(Stack *s) {
    return s->top == 0 ? true : false;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity ? true : false;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top++] = n;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    *n = s->items[--s->top];
    return true;
}

void stack_print(Stack *s) {
    printf("----Stack----\n");
    printf("top:%u\n", s->top);
}

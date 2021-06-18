#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//ref@asgn4.pdf : section 6. Representing Paths whose subsections define for the interface for the path ADT.

struct Path {
    Stack *vertices; // The vertices comprising the path .
    uint32_t length; // The total length of the path .
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0; //initial vertices and length after creating pointer and memory
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices); //delete stack
        assert((*p)->vertices == NULL);
        free(*p); //free pointer
        *p = NULL; //set pointer to null
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    bool flag = false;
    uint32_t u = 0;
    uint32_t increase_length = 0;
    flag = stack_peek(p->vertices, &u);
    increase_length = graph_edge_weight(G, u, v);
    p->length += increase_length;
    return stack_push(p->vertices, v) && flag;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    bool flag = false;
    uint32_t u = 0;
    uint32_t decrease_length = 0;
    flag = stack_pop(p->vertices, v);
    flag = stack_peek(p->vertices, &u) && flag;
    decrease_length = graph_edge_weight(G, u, *v);
    p->length -= decrease_length;
    return flag;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length; //return length directly
}

void path_copy(Path *dst, Path *src) {
    //Assuming that the destination path dst is properly initialized
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %u\n", path_length(p));
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
    return;
}

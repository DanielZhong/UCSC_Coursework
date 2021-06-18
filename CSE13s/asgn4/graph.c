#include "graph.h"

#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->vertices = vertices;
    g->undirected = undirected;
    for (uint32_t i = 0; i < vertices; i++) {
        g->visited[i] = false;
    }
    for (uint32_t i = 0; i < vertices; i++) {
        //use calloc to make sure each cell of the adjacency matrix is set to zero;
        for (uint32_t j = 0; j < vertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

void graph_delete(Graph **G) {
    if (*G) { //if *G is not NULL;
        free(*G);
        *G = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    bool flag = false;
    //if both vertices are within bounds
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;
        //If the graph is undirected, add an edge, also with weight k from j to i
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        flag = true;
    }
    return flag;
}

//Return true if vertices i and j are within bounds and there exists an edge from i to j.
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    bool flag = false;
    //if both vertices are within bounds
    if (i < G->vertices && j < G->vertices && G->matrix[i][j] != 0) {
        flag = true;
    }

    return flag;
}

//Return the weight of the edge from vertex i to vertex j.
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    uint32_t weight = 0;
    //If both i and j are within bounds
    if (i < G->vertices && j < G->vertices && graph_has_edge(G, i, j)) {
        weight = G->matrix[i][j];
    }
    return weight;
}

bool graph_visited(Graph *G, uint32_t v) {
    bool flag = false;
    //make sure vertex v is within bounds
    if (v < G->vertices && G->visited[v]) {
        flag = true;
    }
    return flag;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    //If vertex v is within bounds, mark v as visited.
    if (v < G->vertices) {
        G->visited[v] = true;
    }
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    //If vertex v is within bounds, mark v as unvisited.
    if (v < G->vertices) {
        G->visited[v] = false;
    }
    return;
}

void graph_print(Graph *G) {
    printf("====Graph====\n");
    printf("vertices:%u\n", G->vertices);
    printf("undirected:%s\n", G->undirected ? "true" : "false");
    printf("visited:\n|");
    for (uint32_t i = 0; i < G->vertices; i++) {
        printf("%s|", G->visited[i] ? "1" : "0");
    }
    printf("\nmatrix:\n");
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("|%u", G->matrix[i][j]);
        }
        printf("|\n");
    }
    printf("=============\n");
}

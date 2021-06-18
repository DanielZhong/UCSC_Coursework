#include "danielz.h"

#include <stdio.h>
#include <string.h>

uint32_t recursive = 0;

//-h help message in main function
void help_message() {
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph\n");
    printf("  -v             Enable verbose printing\n");
    printf("  -h             Program usage and help\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default:stdout)\n");
}

//inspired by pdf: DFS() pseudocode
void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {
    //ref:question@568:https://piazza.com/class/kmfs2bmdr9syz?cid=568
    recursive++;
    path_push_vertex(curr, v, G);
    graph_mark_visited(G, v);
    //just recive the poped vertex from path
    uint32_t temp_v;

    //check whether go through all of the vertices
    if (path_vertices(curr) == graph_vertices(G)) {
        //check if there is a direct connection from the last vertex to the first
        if (graph_has_edge(G, v, START_VERTEX)) {
            path_push_vertex(curr, START_VERTEX, G);
            //compare the shortest path to curr path
            if (path_length(curr) < path_length(shortest) || path_vertices(shortest) == 0) {
                //check verbose print, to print all Hamiltonian path
                if (verbose) {
                    path_print(curr, outfile, cities);
                }
                path_copy(shortest, curr);
            }
            path_pop_vertex(curr, &temp_v, G);
        }
    }

    //for all edges from v to w
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        //if this edge in G. adjacentEdges (v)
        if (graph_has_edge(G, v, w)) {
            //if vertex w is not labeled as visited
            if (!graph_visited(G, w)) {
                //inspierd by Eugene Chou in question@567 : https://piazza.com/class/kmfs2bmdr9syz?cid=567
                if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                    dfs(G, w, curr, shortest, cities, outfile, verbose);
                }
            }
        }
    }
    path_pop_vertex(curr, &temp_v, G);
    graph_mark_unvisited(G, v);
}

// ref@C_Programming_Language_by_Kernighan_and_Ritchie : chapter 7.7
int m_getline(char *line, int max, FILE *fp) {
    if (fgets(line, max, fp) == NULL) {
        return 0;
    }
    return strlen(line);
}

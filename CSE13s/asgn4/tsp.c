#include "danielz.h"
#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <errno.h> //error EINVAL
#include <stdbool.h> // For bool
#include <stdio.h> // For printf(), fgets(), fscanf()
#include <stdlib.h> // For atoi() and strtoul()  inspired by asgn3
#include <string.h> // For strdup()
#include <unistd.h> // For getopt()
#define OPTIONS  "hvui:o:"
#define MAX_LINE 1024
#define TRIPLE   3

int main(int argc, char **argv) {
    int opt = 0;
    bool undirected = false;
    bool verbose_print = false;

    FILE *infp = stdin;
    FILE *outfp = stdout;
    //command options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_message();
            exit(0);
            break;
        case 'v': verbose_print = true; break;
        case 'u': undirected = true; break;
        case 'i':
            infp = fopen(optarg, "r");
            if (infp == NULL || errno == EINVAL) { //if can't input file
                fprintf(stderr, "Error: failed to open infile.\n");
                exit(1);
            }
            break;
        case 'o':
            outfp = fopen(optarg, "w");
            if (outfp == NULL || errno == EINVAL) { //if can't output file
                fprintf(stderr, "Error: failed to open outfile.\n");
                exit(1);
            }
            break;
        }
    }
    //read graph from infile
    uint32_t n;
    //read the first number, which is the number of vetices
    fscanf(infp, "%u\n", &n);
    //error message
    if (n <= 1) {
        fprintf(stderr, "There's nowhere to go.\n");
        fclose(infp);
        fclose(outfp);
        exit(1);
    }

    //error message
    if (n > VERTICES) {
        fprintf(stderr, "Error: the number specified is greater than VERTICES\n");
        fclose(infp);
        fclose(outfp);
        exit(1);
    }

    //read n city names
    char *cities
        [n]; //create pointer array(memory = number of vertices) to save string in .graph files
    char line[MAX_LINE];
    int line_length = 0;
    for (uint32_t i = 0; i < n; i++) {
        line_length = m_getline(line, MAX_LINE,
            infp); //read 1 line string and save it to line_length, in m_getline function, fget and save strings to line[] and return length
        //ref@asgn4.pdf : Specifics 3.
        if (line_length == 0) { //exit condition, if no more lines to read(if m_getline return 0)
            fprintf(stderr, "Error: the line is malformed.\n");
            for (uint32_t j = 0; j < i; j++) {
                free(cities[j]);
            }
            fclose(infp);
            fclose(outfp);
            exit(1);
        }
        //ref@asgn4.pdf : Specifics 3
        cities[i] = (char *) strdup(line);
        cities[i][line_length - 1] = '\0'; // change \n to \0 after save it to cities[]
    }

    //create graph
    Graph *g = graph_create(n, undirected);
    //read edges<u,v,w> from infile
    uint32_t u, v, w;
    int match_items = 0;
    while ((match_items = fscanf(infp, "%u %u %u", &u, &v, &w)) != EOF) { //read all 3 sets
        if (match_items != TRIPLE) { //if in not 3 numbers each line from input file
            fprintf(stderr, "Error: the line is malformed.\n");
            for (uint32_t j = 0; j < n; j++) {
                free(cities[j]);
            }
            graph_delete(&g);
            fclose(infp);
            fclose(outfp);
            exit(1);
        }
        graph_add_edge(g, u, v, w);
    }
    //record current path and shortest path
    Path *curr = path_create();
    Path *shortest = path_create();
    //use dfs() function to find Hamiltonian path
    dfs(g, START_VERTEX, curr, shortest, cities, outfp, verbose_print);

    //print shortest path
    path_print(shortest, outfp, cities);
    printf("Total recursive calls: %d\n", recursive);

    //delete path
    path_delete(&curr);
    path_delete(&shortest);

    //delete graph
    graph_delete(&g);

    //free cities created by strdup()
    for (uint32_t i = 0; i < n; i++) {
        free(cities[i]);
    }

    //close file pointer opened by fopen()
    fclose(infp);
    fclose(outfp);

    return 0;
}

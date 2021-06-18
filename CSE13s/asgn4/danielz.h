#ifndef __DANIELZ_H__
#define __DANIELZ_H__

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdint.h>

void help_message();

//total number of recursive calls to dfs().
extern uint32_t recursive;

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose);

//ref@<<K&R C programming>>
int m_getline(char *line, int max, FILE *fp);

#endif

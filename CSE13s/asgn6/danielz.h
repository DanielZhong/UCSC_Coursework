#ifndef __DANIELZ_H__
#define __DANIELZ_H__

#include "code.h"
#include "defines.h"
#include "node.h"

void post_order_traverse(Node *root, Code *c, Code table[static ALPHABET]);

void write_tree(int outfile, Node *root);

void help_encode(void);

void help_decode(void);
#endif

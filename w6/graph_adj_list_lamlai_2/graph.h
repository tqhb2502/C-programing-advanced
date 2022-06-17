#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"

typedef JRB Graph;

Graph create_graph();
void add_edge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int get_adjacent_vertices(Graph g, int v, int *output);
void drop_graph(Graph g);

#endif
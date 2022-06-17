#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef JRB Graph;

Graph create_graph();
void add_edge(Graph, int, int);
int adjacent(Graph, int, int);
int get_adjacent_vertices(Graph, int, int *);
void bfs(Graph, int, int, void (*)(int));
void dfs(Graph, int, int, void (*)(int));
void drop_graph(Graph);

#endif
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph, int, int);
int adjacent(Graph, int, int);
int getAdjacentVertices(Graph, int, int *);
void BFS(Graph, int, int, void(*)(int));
void DFS(Graph, int, int, void(*)(int));
void dropGraph(Graph);

#endif
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"

typedef JRB Graph;

Graph createGraph();
void addDirectedEdge(Graph, int, int);
void addEdge(Graph, int, int);
int adjacent(Graph, int, int);
int getAdjacentVertices(Graph, int, int *);
void dropGraph(Graph);

#endif
#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 1000000000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph, int, char *);
JRB getVertex(Graph, int);
void addEdge(Graph, int, int, double);
double getEdgeValue(Graph, int, int);
int indegree(Graph, int, int *);
int outdegree(Graph, int, int *);
void BFS(Graph, int, int, void (*)(int));
void DFS(Graph, int, int, void (*)(int));
double shortestPath(Graph, int, int, int *, int *);
void dropGraph(Graph);

#endif
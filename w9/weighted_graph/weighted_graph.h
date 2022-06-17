#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph, int, char *);
char *getVertex(Graph, int);
void addEdge(Graph, int, int, double);
double getEdgeValue(Graph, int, int);
int indegree(Graph, int, int *);
int outdegree(Graph, int, int *);
double shortestPath(Graph, int, int, int *, int *);
void dropGraph(Graph);

#endif
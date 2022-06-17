#ifndef __DIRECTED_GRAPH_H__
#define __DIRECTED_GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph, int, char *);
char *getVertex(Graph, int);
void addEdge(Graph, int, int);
int hasEdge(Graph, int, int);
int indegree(Graph, int, int *);
int outdegree(Graph, int, int *);
int DAG(Graph);
void dropGraph(Graph);

#endif
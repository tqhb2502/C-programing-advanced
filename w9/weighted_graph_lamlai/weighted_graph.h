#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 10000000

typedef struct {
	JRB vertices;
	JRB edges;
} Graph;

Graph create_graph();
void add_vertex(Graph, int, char *);
char *get_vertex(Graph, int);
void add_edge(Graph, int, int, double);
double get_edge_value(Graph, int, int);
int indegree(Graph, int, int *);
int outdegree(Graph, int, int *);
double shortest_path(Graph, int, int, int *, int *);
void drop_graph(Graph);

#endif
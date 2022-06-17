#ifndef __DIRECTED_GRAPH_H__
#define __DIRECTED_GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef struct {
	JRB vertices;
	JRB edges;
} Graph;

Graph create_graph();
void add_vertex(Graph, int, char *);
char *get_vertex(Graph, int);
void add_edge(Graph, int, int);
int has_edge(Graph, int, int);
int indegree(Graph, int);
int outdegree(Graph, int);
int is_DAG(Graph);
void topo_sort(Graph, int *, int *);
void drop_graph(Graph);

#endif
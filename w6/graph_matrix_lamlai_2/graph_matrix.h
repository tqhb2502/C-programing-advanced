#ifndef __GRAPH_MATRIX_H__
#define __GRAPH_MATRIX_H__

typedef struct {
	int *matrix;
	int sizemax;
} Graph;

Graph create_graph(int sizemax);
void add_edge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int get_adjacent_vertices(Graph g, int v, int *output);
void drop_graph(Graph g);

#endif
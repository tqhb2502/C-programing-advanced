#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

Graph create_graph(int sizemax) {
	Graph g;
	g.matrix = (int *) malloc(sizemax * sizemax * sizeof(int));
	g.sizemax = sizemax;
	return g;
}

void add_edge(Graph g, int v1, int v2) {
	g.matrix[v1 * g.sizemax + v2] = 1;
	g.matrix[v2 * g.sizemax + v1] = 1;
}

int adjacent(Graph g, int v1, int v2) {
	return g.matrix[v1 * g.sizemax + v2];
}

int get_adjacent_vertices(Graph g, int v, int *output) {
	int count = 0;

	for (int i = 0; i < g.sizemax; i++)
		if (g.matrix[v * g.sizemax + i])
		{
			output[count] = i;
			count++;
		}

	return count;
}

void drop_graph(Graph g){
	free(g.matrix);
}
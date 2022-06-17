#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

int main() {
	int i, n, output[100];
    Graph g = create_graph(100);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    n = get_adjacent_vertices (g, 1, output);
    if (n==0) printf("No adjacent vertices of node 1\n");
    else
    {
        printf("Adjacent vertices of node 1:");
        for (i=0; i<n; i++) printf("%5d", output[i]);
        printf("\n");
    }
	return 0;
}
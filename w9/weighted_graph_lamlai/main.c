#include <stdlib.h>
#include <stdio.h>
#include "weighted_graph.h"

int main()
{
    Graph g = create_graph();
    add_vertex(g, 0, "CS102"); add_vertex(g, 1, "CS140");
    add_vertex(g, 2, "CS160"); add_vertex(g, 3, "CS302");
    add_vertex(g, 4, "CS311"); add_vertex(g, 5, "MATH300");
    add_edge(g, 0, 1, 1.5); add_edge(g, 0, 2, 3.0); add_edge(g, 2, 3, 4.0);
    add_edge(g, 1, 3, 6.0); add_edge(g, 5, 4, 1.2); add_edge(g, 3, 4, 1.0);
    add_edge(g, 2, 5, 1.0);
    int s = 0, t = 4, length, path[1000];
    double weight = shortest_path(g, s, t, path, &length);
    if (weight == INFINITIVE_VALUE)
        printf("No path between %d and %d\n", s, t);
    else {
        printf("Path between %d and %d:\n", s, t);
        for (int i=0; i<length; i++) printf("%d ", path[i]);
        printf("\n");
        printf("Total weight: %lf\n", weight);
    }
    return 0;
}
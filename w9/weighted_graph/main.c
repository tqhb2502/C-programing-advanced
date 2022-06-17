#include <stdlib.h>
#include <stdio.h>
#include "weighted_graph.h"

int main()
{
    Graph g = createGraph();
    addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
    addEdge(g, 0, 1, 1.5); addEdge(g, 0, 2, 3.0); addEdge(g, 2, 3, 4.0);
    addEdge(g, 1, 3, 6.0); addEdge(g, 5, 4, 10.2); addEdge(g, 3, 4, 1.0);
    int s = 0, t = 3, length, path[1000];
    double weight = shortestPath(g, s, t, path, &length);
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
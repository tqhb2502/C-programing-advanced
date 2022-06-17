#include <stdlib.h>
#include "graph_matrix.h"

Graph createGraph(int sizemax)
{
    Graph g;
    g.matrix = (int *)malloc(sizemax * sizemax * sizeof(int));
    for (int i = 0; i < sizemax * sizemax; i++)
        g.matrix[i] = 0;
    g.sizemax = sizemax;
    return g;
}

void addEdge(Graph g, int v1, int v2)
{
    g.matrix[v1 * g.sizemax + v2] = 1;
    g.matrix[v2 * g.sizemax + v1] = 1;
    return;
}

int adjacent(Graph g, int v1, int v2)
{
    return g.matrix[v1 * g.sizemax + v2];
}

int getAdjacentVertices(Graph g, int vertex, int *output)
{
    int count = 0;
    for (int i = vertex * g.sizemax; i < vertex * g.sizemax + g.sizemax; i++)
        if (g.matrix[i] == 1)
        {
            output[count] = i - vertex * g.sizemax;
            count++;
        }
    return count;
}

void dropGraph(Graph g)
{
    free(g.matrix);
    return;
}
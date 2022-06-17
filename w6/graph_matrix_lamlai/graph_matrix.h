#ifndef __GRAPH_MATRIX_H__
#define __GRAPH_MATRIX_H__

typedef struct
{
    int *matrix;
    int sizemax;
} Graph;

Graph createGraph(int);
void addEdge(Graph, int, int);
int adjacent(Graph, int, int);
int getAdjacentVertices(Graph, int, int *);
void dropGraph(Graph);

#endif
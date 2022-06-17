#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void printVertex(int v)
{
    printf("%4d", v);
}

int main() {
    Graph g = create_graph();
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 1, 3);
    add_edge(g, 2, 3);
    add_edge(g, 2, 4);
    add_edge(g, 4, 5);
    printf("BFS: start from node 1 to 4 : ");
    bfs(g, 1, 4, printVertex);
    printf("\n");
    printf("BFS: start from node 1 to all : ");
    bfs(g, 1, -1, printVertex);
    printf("\n");
    printf("DFS: start from node 1 to 4 : ");
    dfs(g, 1, 4, printVertex);
    printf("\n");
    printf("DFS: start from node 1 to all : ");
    dfs(g, 1, -1, printVertex);
    printf("\n");
    return 0;
}
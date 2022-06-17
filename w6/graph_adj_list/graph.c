#include <stdlib.h>
#include "graph.h"

Graph createGraph()
{
    JRB g = make_jrb();
    return g;
}

void addDirectedEdge(Graph g, int v1, int v2)
{
    JRB res = jrb_find_int(g, v1);
    if (res == NULL)
    {
        JRB adj_list = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(adj_list));
        jrb_insert_int(adj_list, v2, new_jval_i(1));
    }
    else jrb_insert_int((JRB)res->val.v, v2, new_jval_i(1));
    return;
}

void addEdge(Graph g, int v1, int v2)
{
    addDirectedEdge(g, v1, v2);
    addDirectedEdge(g, v2, v1);
    return;
}

int adjacent(Graph g, int v1, int v2)
{
    JRB node = jrb_find_int(g, v1);
    JRB adj = jrb_find_int((JRB)node->val.v, v2);
    if (adj == NULL) return 0;
    return 1;
}

int getAdjacentVertices(Graph g, int vertex, int *output)
{
    JRB node = jrb_find_int(g, vertex);
    JRB adj_list = (JRB)node->val.v;
    int count = 0;
    jrb_traverse(node, adj_list)
    {
        output[count] = node->key.i;
        count++;
    }
    return count;
}

void dropGraph(Graph g)
{
    JRB node;
    jrb_traverse(node, g)
        jrb_free_tree((JRB)node->val.v);
    jrb_free_tree(g);
    return;
}
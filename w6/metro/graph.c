#include <stdlib.h>
#include "graph.h"

Graph createGraph()
{
    return make_jrb();
}

void addEdge(Graph g, int v1, int v2)
{
    JRB node, adj_list;
    node = jrb_find_int(g, v1);
    if (node == NULL)
    {
        adj_list = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(adj_list));
        jrb_insert_int(adj_list, v2, new_jval_i(1));
    }
    else
    {
        adj_list = (JRB)node->val.v;
        jrb_insert_int(adj_list, v2, new_jval_i(1));
    }

    node = jrb_find_int(g, v2);
    if (node == NULL)
    {
        adj_list = make_jrb();
        jrb_insert_int(g, v2, new_jval_v(adj_list));
        jrb_insert_int(adj_list, v1, new_jval_i(1));
    }
    else
    {
        adj_list = (JRB)node->val.v;
        jrb_insert_int(adj_list, v1, new_jval_i(1));
    }
    return;
}

int adjacent(Graph g, int v1, int v2)
{
    JRB node, adj_list;
    node = jrb_find_int(g, v1);
    adj_list = (JRB)node->val.v;
    if (jrb_find_int(adj_list, v2) == NULL) return 0;
    return 1;
}

int getAdjacentVertices(Graph g, int vertex, int *output)
{
    JRB node, adj_list;
    node = jrb_find_int(g, vertex);
    adj_list = (JRB)node->val.v;
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
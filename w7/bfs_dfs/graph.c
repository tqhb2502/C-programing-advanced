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

void BFS(Graph g, int start, int stop, void (*func)(int))
{
    JRB visited, node, adj_list;
    visited = make_jrb();
    Dllist queue, queue_node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    jrb_insert_int(visited, start, new_jval_i(1));
    int u, v;
    while (!dll_empty(queue))
    {
        queue_node = dll_first(queue);
        u = queue_node->val.i;
        dll_delete_node(queue_node);
        func(u);
        if (u == stop) break;
        node = jrb_find_int(g, u);
        if (node == NULL) continue;
        adj_list = (JRB)node->val.v;
        jrb_traverse(node, adj_list)
        {
            v = node->key.i;
            if (jrb_find_int(visited, v) == NULL)
            {
                dll_append(queue, new_jval_i(v));
                jrb_insert_int(visited, v, new_jval_i(1));
            }
        }
    }
    return;
}

void DFS(Graph g, int start, int stop, void (*func)(int))
{
    JRB visited, node, adj_list;
    visited = make_jrb();
    Dllist stack, stack_node;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    jrb_insert_int(visited, start, new_jval_i(1));
    int u, v;
    while (!dll_empty(stack))
    {
        stack_node = dll_last(stack);
        u = stack_node->val.i;
        dll_delete_node(stack_node);
        func(u);
        if (u == stop) break;
        node = jrb_find_int(g, u);
        if (node == NULL) continue;
        adj_list = (JRB)node->val.v;
        jrb_traverse(node, adj_list)
        {
            v = node->key.i;
            if (jrb_find_int(visited, v) == NULL)
            {
                dll_append(stack, new_jval_i(v));
                jrb_insert_int(visited, v, new_jval_i(1));
            }
        }
    }
    return;
}
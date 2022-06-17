#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "directed_graph.h"

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name)
{
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
    return;
}

char *getVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    return node->val.s;
}

void addEdge(Graph g, int v1, int v2)
{
    JRB node, adj_list;
    node = jrb_find_int(g.edges, v1);
    if (node == NULL)
    {
        adj_list = make_jrb();
        jrb_insert_int(g.edges, v1, new_jval_v(adj_list));
        jrb_insert_int(adj_list, v2, new_jval_i(1));
    }
    else
    {
        adj_list = (JRB)node->val.v;
        jrb_insert_int(adj_list, v2, new_jval_i(1));
    }
    return;
}

int hasEdge(Graph g, int v1, int v2)
{
    JRB node, adj_list;
    node = jrb_find_int(g.edges, v1);
    if (node == NULL) return 0;
    adj_list = (JRB)node->val.v;
    if (jrb_find_int(adj_list, v2) == NULL) return 0;
    return 1;
}

int indegree(Graph g, int v, int *output)
{
    int count = 0;
    JRB node, adj_list;
    jrb_traverse(node, g.edges)
    {
        adj_list = (JRB)node->val.v;
        if (jrb_find_int(adj_list, v) != NULL)
        {
            output[count] = node->key.i;
            count++;
        }
    }
    return count;
}

int outdegree(Graph g, int v, int *output)
{
    int count = 0;
    JRB node, adj_list;
    node = jrb_find_int(g.edges, v);
    adj_list = (JRB)node->val.v;
    jrb_traverse(node, adj_list)
    {
        output[count] = node->key.i;
        count++;
    }
    return count;
}

int DFS(Graph g, int start, int stop)
{
    int result = 0;
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
        if (u == stop) break;
        node = jrb_find_int(g.edges, u);
        if (node == NULL) continue;
        adj_list = (JRB)node->val.v;
        jrb_traverse(node, adj_list)
        {
            v = node->key.i;
            if (v == start) result = 1;
            if (jrb_find_int(visited, v) == NULL)
            {
                dll_append(stack, new_jval_i(v));
                jrb_insert_int(visited, v, new_jval_i(1));
            }
        }
    }
    return result;
}

int DAG(Graph g)
{
    JRB node;
    jrb_traverse(node, g.vertices)
        if (DFS(g, node->key.i, -1) == 1) return 0;
    return 1;
}

void topoSort(Graph g, int *output, int *n)
{
    JRB indeg;
    JRB node, adj_list, node_2, tmp;
    int curIndeg;
    Dllist list, list_node;
    indeg = make_jrb();
    jrb_traverse(node, g.vertices)
        jrb_insert_int(indeg, node->key.i, new_jval_i(0));
    jrb_traverse(node, g.edges)
    {
        adj_list = (JRB)node->val.v;
        jrb_traverse(node_2, adj_list)
        {
            tmp = jrb_find_int(indeg, node_2->key.i);
            curIndeg = tmp->val.i;
            jrb_delete_node(tmp);
            jrb_insert_int(indeg, node_2->key.i, new_jval_i(curIndeg + 1));
        }
    }
    list = new_dllist();
    jrb_traverse(node, g.vertices)
    {
        tmp = jrb_find_int(indeg, node->key.i);
        if (tmp->val.i == 0)
            dll_append(list, tmp->key);
    }
    int u, v;
    while (!dll_empty(list))
    {
        list_node = dll_first(list);
        u = list_node->val.i;
        dll_delete_node(list_node);
        output[*n] = u;
        (*n)++;
        node = jrb_find_int(g.edges, u);
        if (node == NULL) continue;
        adj_list = (JRB)node->val.v;
        jrb_traverse(node, adj_list)
        {
            v = node->key.i;
            tmp = jrb_find_int(indeg, v);
            curIndeg = tmp->val.i;
            jrb_delete_node(tmp);
            jrb_insert_int(indeg, v, new_jval_i(curIndeg - 1));
            if (curIndeg - 1 == 0)
                dll_append(list, new_jval_i(v));
        }
    }
    return;
}

void dropGraph(Graph g)
{
    JRB node, adj_list;
    jrb_traverse(node, g.edges)
    {
        adj_list = (JRB)node->val.v;
        jrb_free_tree(adj_list);
    }
    jrb_free_tree(g.edges);
    jrb_traverse(node, g.vertices)
        free(node->val.s);
    jrb_free_tree(g.vertices);
    return;
}
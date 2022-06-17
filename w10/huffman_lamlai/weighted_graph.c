#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "weighted_graph.h"

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

JRB getVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    return node;
}

void addEdge(Graph g, int v1, int v2, double weight)
{
    JRB node, adj_list;
    node = jrb_find_int(g.edges, v1);
    if (node == NULL)
    {
        adj_list = make_jrb();
        jrb_insert_int(g.edges, v1, new_jval_v(adj_list));
        jrb_insert_int(adj_list, v2, new_jval_d(weight));
    }
    else
    {
        adj_list = (JRB)jval_v(node->val);
        jrb_insert_int(adj_list, v2, new_jval_d(weight));
    }
    return;
}

double getEdgeValue(Graph g, int v1, int v2)
{
    JRB node, adj_list, tmp;
    node = jrb_find_int(g.edges, v1);
    adj_list = (JRB)jval_v(node->val);
    tmp = jrb_find_int(adj_list, v2);
    if (tmp == NULL) return INFINITIVE_VALUE;
    return jval_d(tmp->val);
}

int indegree(Graph g, int v, int *output)
{
    int count = 0;
    JRB node, adj_list;
    jrb_traverse(node, g.edges)
    {
        adj_list = (JRB)jval_v(node->val);
        if (jrb_find_int(adj_list, v) != NULL)
        {
            output[count] = jval_i(node->key);
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
    adj_list = (JRB)jval_v(node->val);
    jrb_traverse(node, adj_list)
    {
        output[count] = jval_i(node->key);
        count++;
    }
    return count;
}

int relax(int u, int v, double w, JRB d, JRB parent)
{
    double du, dv;
    JRB tmp;
    tmp = jrb_find_int(d, u);
    du = jval_d(tmp->val);
    tmp = jrb_find_int(d, v);
    dv = jval_d(tmp->val);
    if (dv > du + w)
    {
        tmp = jrb_find_int(d, v);
        jrb_delete_node(tmp);
        jrb_insert_int(d, v, new_jval_d(du + w));
        tmp = jrb_find_int(parent, v);
        jrb_delete_node(tmp);
        jrb_insert_int(parent, v, new_jval_i(u));
        return 1;
    }
    return 0;
}

double getShortestPathResult(int s, int t, int *path, int *length, JRB d, JRB parent)
{
    JRB node;
    node = jrb_find_int(d, t);
    if (jval_d(node->val) == INFINITIVE_VALUE) return INFINITIVE_VALUE;
    Dllist list = new_dllist();
    Dllist list_node;
    int tmp = t;
    while (tmp != s)
    {
        dll_append(list, new_jval_i(tmp));
        node = jrb_find_int(parent, tmp);
        tmp = jval_i(node->val);
    }
    int count = 0;
    path[count] = s;
    count++;
    while (!dll_empty(list))
    {
        list_node = dll_last(list);
        path[count] = jval_i(list_node->val);
        count++;
        dll_delete_node(list_node);
    }
    (*length) = count;
    node = jrb_find_int(d, t);
    return jval_d(node->val);
}

double shortestPath(Graph g, int s, int t, int *path, int *length)
{
    JRB d, parent, node, adj_list, node_2;
    d = make_jrb();
    parent = make_jrb();
    jrb_traverse(node, g.vertices)
    {
        jrb_insert_int(d, jval_i(node->key), new_jval_d(INFINITIVE_VALUE));
        jrb_insert_int(parent, jval_i(node->key), new_jval_i(-1));
    }
    Dllist pqueue, pqueue_node;
    pqueue = new_dllist();
    node = jrb_find_int(d, s);
    jrb_delete_node(node);
    jrb_insert_int(d, s, new_jval_d(0));
    dll_append(pqueue, new_jval_i(s));
    int tmp, u, v, result;
    double min, w;
    while (!dll_empty(pqueue))
    {
        min = INFINITIVE_VALUE;
        dll_traverse(pqueue_node, pqueue)
        {
            tmp = jval_i(pqueue_node->val);
            node = jrb_find_int(d, tmp);
            if (min > jval_d(node->val))
            {
                min = jval_d(node->val);
                u = tmp;
            }
        }
        if (u == t) break;
        dll_traverse(pqueue_node, pqueue)
            if (jval_i(pqueue_node->val) == u)
            {
                dll_delete_node(pqueue_node);
                break;
            }
        node = jrb_find_int(g.edges, u);
        if (node == NULL) continue;
        adj_list = (JRB)jval_v(node->val);
        jrb_traverse(node, adj_list)
        {
            v = jval_i(node->key);
            w = jval_d(node->val);
            result = relax(u, v, w, d, parent);
            if (result == 1)
                dll_append(pqueue, new_jval_i(v));
        }
    }
    return getShortestPathResult(s, t, path, length, d, parent);
}

void printVertex(Graph g, int id) {
    JRB treeNode = getVertex(g, id);
    printf("%d *%s*\n", jval_i(treeNode->key), jval_s(treeNode->val));
    return;
}

void BFS(Graph g, int start, int stop)
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
        printVertex(g, u);
        if (u == stop) break;
        node = jrb_find_int(g.edges, u);
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

void DFS(Graph g, int start, int stop)
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
        printVertex(g, u);
        if (u == stop) break;
        node = jrb_find_int(g.edges, u);
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
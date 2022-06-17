#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weighted_graph.h"

Graph create_graph() {
	Graph g;
	g.vertices = make_jrb();
	g.edges = make_jrb();
	return g;
}

void add_vertex(Graph g, int key, char *str) {
	jrb_insert_int(g.vertices, key, new_jval_s(strdup(str)));
}

char *get_vertex(Graph g, int key) {
	JRB node = jrb_find_int(g.vertices, key);
	if (node == NULL) return NULL;
	return jval_s(node->val);
}

void add_edge(Graph g, int v1, int v2, double w) {
	JRB node, adj_list;

	node = jrb_find_int(g.edges, v1);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v2, new_jval_d(w));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v2, new_jval_d(w));
	}
}

double get_edge_value(Graph g, int v1, int v2) {
	JRB node = jrb_find_int(g.edges, v1);
	if (node == NULL) return INFINITIVE_VALUE;

	JRB adj_list = (JRB) jval_v(node->val);

	JRB tmp = jrb_find_int(adj_list, v2);
	if (tmp == NULL) return INFINITIVE_VALUE;
	return jval_d(tmp->val);
}

int indegree(Graph g, int v, int *output) {
	JRB node, adj_list;

	int count = 0;
	jrb_traverse(node, g.edges) {
		adj_list = (JRB) jval_v(node->val);
		if (jrb_find_int(adj_list, v) != NULL) {
			output[count] = jval_i(node->key);
			count++;
		}
	}

	return count;
}

int outdegree(Graph g, int v, int *output) {
	JRB node = jrb_find_int(g.edges, v);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);

	int count = 0;
	jrb_traverse(node, adj_list) {
		output[count] = jval_i(node->key);
		count++;
	}

	return count;
}

int relax(int u, int v, double w, JRB d, JRB parent) {
	JRB node;
	double du, dv;

	node = jrb_find_int(d, u);
	du = jval_d(node->val);

	node = jrb_find_int(d, v);
	dv = jval_d(node->val);

	if (dv > du + w) {
		node = jrb_find_int(d, v);
		jrb_delete_node(node);
		jrb_insert_int(d, v, new_jval_d(du + w));

		node = jrb_find_int(parent, v);
		jrb_delete_node(node);
		jrb_insert_int(parent, v, new_jval_i(u));

		return 1;
	}

	return 0;
}

double get_result(int s, int t, JRB d, JRB parent, int *path, int *length) {
	JRB node = jrb_find_int(parent, t);
	if (jval_i(node->val) == -1) return INFINITIVE_VALUE;

	Dllist list = new_dllist();

	int tmp = t;
	while (tmp != -1) {
		dll_append(list, new_jval_i(tmp));
		node = jrb_find_int(parent, tmp);
		tmp = jval_i(node->val);
	}

	Dllist listNode;

	*length = 0;
	while (!dll_empty(list)) {
		listNode = dll_last(list);
		path[(*length)] = jval_i(listNode->val);
		(*length)++;
		dll_delete_node(listNode);
	}

	node = jrb_find_int(d, t);
	return jval_d(node->val);
}

double shortest_path(Graph g, int s, int t, int *path, int *length) {
	JRB d = make_jrb();
	JRB parent = make_jrb();

	JRB node;

	jrb_traverse(node, g.vertices) {
		int key = jval_i(node->key);

		jrb_insert_int(d, key, new_jval_d(INFINITIVE_VALUE));
		jrb_insert_int(parent, key, new_jval_i(-1));
	}

	Dllist pqueue = new_dllist();
	dll_append(pqueue, new_jval_i(s));

	node = jrb_find_int(d, s);
	jrb_delete_node(node);
	jrb_insert_int(d, s, new_jval_i(0));

	int u, v;
	double min, du, w;
	JRB adj_list;
	Dllist pqueueNode, tmp;
	while (!dll_empty(pqueue)) {
		min = INFINITIVE_VALUE;

		dll_traverse(tmp, pqueue) {
			u = jval_i(tmp->val);
			node = jrb_find_int(d, u);
			du = jval_d(node->val);

			if (du < min) {
				min = du;
				pqueueNode = tmp;
			}
		}

		u = jval_i(pqueueNode->val);
		dll_delete_node(pqueueNode);

		if (u == t) break;

		node = jrb_find_int(g.edges, u);
		if (node == NULL) continue;

		adj_list = (JRB) jval_v(node->val);
		jrb_traverse(node, adj_list) {
			v = jval_i(node->key);
			w = jval_d(node->val);

			if (relax(u, v, w, d, parent)) {
				dll_append(pqueue, new_jval_i(v));
			}
		}
	}

	return get_result(s, t, d, parent, path, length);
}

void drop_graph(Graph g) {
	JRB node;

	jrb_traverse(node, g.vertices) {
		free(jval_s(node->val));
	}
	jrb_free_tree(g.vertices);

	jrb_traverse(node, g.edges) {
		jrb_free_tree((JRB) jval_v(node->val));
	}
	jrb_free_tree(g.edges);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directed_graph.h"

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

void add_edge(Graph g, int v1, int v2) {
	JRB node, adj_list;

	node = jrb_find_int(g.edges, v1);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v2, new_jval_i(1));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v2, new_jval_i(1));
	}
}

int has_edge(Graph g, int v1, int v2) {
	JRB node = jrb_find_int(g.edges, v1);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);
	if (jrb_find_int(adj_list, v2) == NULL) return 0;
	return 1;
}

int indegree(Graph g, int v) {
	JRB node, adj_list;

	int count = 0;
	jrb_traverse(node, g.edges) {
		adj_list = (JRB) jval_v(node->val);
		if (jrb_find_int(adj_list, v) != NULL) {
			count++;
		}
	}

	return count;
}

int outdegree(Graph g, int v) {
	JRB node = jrb_find_int(g.edges, v);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);

	int count = 0;
	jrb_traverse(node, adj_list) {
		count++;
	}

	return count;
}

int dfs(Graph g, int start, int stop) {
	JRB visited = make_jrb();

	Dllist stack = new_dllist();

	dll_append(stack, new_jval_i(start));
	jrb_insert_int(visited, start, new_jval_i(1));

	int u, v;
	Dllist stackNode;
	JRB node, adj_list;
	while (!dll_empty(stack)) {
		stackNode = dll_last(stack);
		u = jval_i(stackNode->val);
		dll_delete_node(stackNode);

		if (u == stop) break;

		node = jrb_find_int(g.edges, u);
		if (node == NULL) continue;

		adj_list = (JRB) jval_v(node->val);
		jrb_traverse(node, adj_list) {
			v = jval_i(node->key);
			if (u == v) return 1;

			if (jrb_find_int(visited, v) == NULL) {
				dll_append(stack, new_jval_i(v));
				jrb_insert_int(visited, v, new_jval_i(1));
			}
		}
	}

	return 0;
}

int is_DAG(Graph g) {
	JRB node;
	jrb_traverse(node, g.vertices) {
		if (dfs(g, jval_i(node->key), -1)) return 0;
	}

	return 1;
}

void topo_sort(Graph g, int *output, int *n) {
	JRB indeg = make_jrb();

	JRB node;

	int key, val;
	jrb_traverse(node, g.vertices) {
		key = jval_i(node->key);
		val = indegree(g, key);
		jrb_insert_int(indeg, key, new_jval_i(val));
	}

	Dllist queue = new_dllist();

	jrb_traverse(node, indeg) {
		if (jval_i(node->val) == 0) {
			dll_append(queue, node->key);
		}
	}

	int u, v, vIndeg;
	Dllist queueNode;
	JRB adj_list, indegNode;
	while (!dll_empty(queue)) {
		queueNode = dll_first(queue);
		u = jval_i(queueNode->val);
		dll_delete_node(queueNode);

		output[(*n)] = u;
		(*n)++;

		node = jrb_find_int(g.edges, u);
		if (node == NULL) continue;

		adj_list = (JRB) jval_v(node->val);
		jrb_traverse(node, adj_list) {
			v = jval_i(node->key);

			indegNode = jrb_find_int(indeg, v);
			vIndeg = jval_i(indegNode->val);

			jrb_delete_node(indegNode);
			jrb_insert_int(indeg, v, new_jval_i(vIndeg - 1));

			if (vIndeg - 1 == 0) {
				dll_append(queue, new_jval_i(v));
			}
		}
	}
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
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph create_graph() {
	return make_jrb();
}

void add_edge(Graph g, int v1, int v2) {
	JRB node, adj_list;

	node = jrb_find_int(g, v1);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g, v1, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v2, new_jval_i(1));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v2, new_jval_i(1));
	}

	node = jrb_find_int(g, v2);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g, v2, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v1, new_jval_i(1));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v1, new_jval_i(1));
	}
}

int adjacent(Graph g, int v1, int v2) {
	JRB node = jrb_find_int(g, v1);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);
	if (jrb_find_int(adj_list, v2) == NULL) return 0;
	return 1;
}

int get_adjacent_vertices(Graph g, int v1, int *output) {
	JRB node = jrb_find_int(g, v1);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);

	int count = 0;
	jrb_traverse(node, adj_list) {
		output[count] = jval_i(node->key);
		count++;
	}

	return count;
}

void bfs(Graph g, int start, int stop, void (*func)(int)) {
	JRB visited = make_jrb();

	Dllist queue = new_dllist();

	dll_append(queue, new_jval_i(start));
	jrb_insert_int(visited, start, new_jval_i(1));

	int u, v;
	Dllist queueNode;
	JRB node, adj_list;
	
	while (!dll_empty(queue)) {
		queueNode = dll_first(queue);
		u = jval_i(queueNode->val);
		dll_delete_node(queueNode);

		func(u);

		if (u == stop) break;

		node = jrb_find_int(g, u);
		if (node == NULL) continue;

		adj_list = (JRB) jval_v(node->val);
		jrb_traverse(node, adj_list) {
			v = jval_i(node->key);
			if (jrb_find_int(visited, v) == NULL) {
				dll_append(queue, new_jval_i(v));
				jrb_insert_int(visited, v, new_jval_i(1));
			}
		}
	}
}

void dfs(Graph g, int start, int stop, void (*func)(int)) {
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

		func(u);

		if (u == stop) break;

		node = jrb_find_int(g, u);
		if (node == NULL) continue;

		adj_list = (JRB) jval_v(node->val);
		jrb_traverse(node, adj_list) {
			v = jval_i(node->key);
			if (jrb_find_int(visited, v) == NULL) {
				dll_append(stack, new_jval_i(v));
				jrb_insert_int(visited, v, new_jval_i(1));
			}
		}
	}
}

void drop_graph(Graph g) {
	JRB node;

	jrb_traverse(node, g) {
		jrb_free_tree((JRB) jval_v(node->val));
	}

	jrb_free_tree(g);
}
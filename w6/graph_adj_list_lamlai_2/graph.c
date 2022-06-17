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

int get_adjacent_vertices(Graph g, int v, int *output) {
	JRB node = jrb_find_int(g, v);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);

	int count = 0;
	jrb_traverse(node, adj_list) {
		output[count] = jval_i(node->key);
		count++;
	}

	return count;
}

void drop_graph(Graph g){
	JRB node;

	jrb_traverse(node, g) {
		jrb_free_tree((JRB) jval_v(node->val));
	}

	jrb_free_tree(g);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

typedef struct {
	JRB CCCD;
	JRB phoneNumber;
	JRB name;
	JRB edges;
	int key;
	int tiepXuc;
} Graph;

Graph create_graph() {
	Graph g;
	g.CCCD = make_jrb();
	g.phoneNumber = make_jrb();
	g.name = make_jrb();
	g.edges = make_jrb();
	g.key = 0;
	g.tiepXuc = 0;
	return g;
}

void add_vertex(Graph g, char *CCCD, char *phoneNumber, char *name) {
	jrb_insert_int(g.CCCD, g.key, new_jval_s(strdup(CCCD)));
	jrb_insert_int(g.phoneNumber, g.key, new_jval_s(strdup(phoneNumber)));
	jrb_insert_int(g.name, g.key, new_jval_s(strdup(name)));
	g.key++;
}

int get_vertex_key_by_CCCD(Graph g, char *CCCD) {
	JRB node;

	jrb_traverse(node, g.CCCD) {
		if (strcmp(jval_s(node->val), CCCD) == 0) {
			return jval_i(node->key);
		}
	}

	return -1;
}

void update_vertex(Graph g, char *CCCD, char *phoneNumber, char *name) {
	int key = get_vertex_key_by_CCCD(g, CCCD);

	if (key == -1) {
		add_vertex(g, CCCD, phoneNumber, name);

		printf("Them cong dan\n");
	} else {
		JRB node;

		node = jrb_find_int(g.phoneNumber, key);
		jrb_delete_node(node);
		jrb_insert_int(g.phoneNumber, key, new_jval_s(strdup(phoneNumber)));

		node = jrb_find_int(g.name, key);
		jrb_delete_node(node);
		jrb_insert_int(g.name, key, new_jval_s(strdup(name)));

		printf("Cap nhat thong tin\n");
	}

	printf("Tong so ban ghi cong dan: %d\n", g.key);
}

void add_edge(Graph g, int v1, int v2, char *day) {
	JRB node, adj_list;

	node = jrb_find_int(g.edges, v1);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v2, new_jval_s(strdup(day)));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v2, new_jval_s(strdup(day)));
	}

	node = jrb_find_int(g.edges, v2);
	if (node == NULL) {
		adj_list = make_jrb();
		jrb_insert_int(g.edges, v2, new_jval_v(adj_list));
		jrb_insert_int(adj_list, v1, new_jval_s(strdup(day)));
	} else {
		adj_list = (JRB) jval_v(node->val);
		jrb_insert_int(adj_list, v1, new_jval_s(strdup(day)));
	}

	g.tiepXuc++;
}

int has_edge(Graph g, int v1, int v2) {
	JRB node = jrb_find_int(g.edges, v1);
	if (node == NULL) return 0;

	JRB adj_list = (JRB) jval_v(node->val);
	if (jrb_find_int(adj_list, v2) == NULL) return 0;
	return 1;
}

void update_edge(Graph g, int v1, int v2, char *day) {
	if (!has_edge(g, v1, v2)) {
		add_edge(g, v1, v2, day);

		printf("Them tiep xuc\n");
	} else {
		JRB node, adj_list;

		node = jrb_find_int(g.edges, v1);
		adj_list = (JRB) jval_v(node->val);
		jrb_delete_node(jrb_find_int(adj_list, v2));
		jrb_insert_int(adj_list, v2, new_jval_s(strdup(day)));

		node = jrb_find_int(g.edges, v2);
		adj_list = (JRB) jval_v(node->val);
		jrb_delete_node(jrb_find_int(adj_list, v1));
		jrb_insert_int(adj_list, v1, new_jval_s(strdup(day)));

		printf("Cap nhat tiep xuc\n");
	}

	printf("Tong so tiep xuc: %d\n", g.tiepXuc);
}

void read_input_file(Graph g) {
	FILE *fp;
	char str[100];

	fp = fopen("DANCU.TXT", "r");
	fgets(str, 100, fp);
	printf("Tong so dinh: %s", str);

	char CCCD[15], phoneNumber[15], name[70];
	while (!feof(fp)) {
		if (fgets(str, 100, fp) == NULL) break;
		if (!feof(fp)) {
			str[strlen(str) - 2] = '\0';	
		}

		strncpy(CCCD, str, 12);
		strncpy(phoneNumber, str + 13, 10);
		strcpy(name, str + 24);

		add_vertex(g, CCCD, phoneNumber, name);
	}

	fclose(fp);

	FILE *fp2 = fopen("TIEPXUC.TXT", "r");
	char str2[100];
	fgets(str2, 100, fp2);
	printf("Tong so canh: %s", str2);

	char CCCD1[15], CCCD2[15], day[15];
	while (!feof(fp2)) {
		if (fgets(str2, 100, fp2) == NULL) break;
		if (!feof(fp2)) {
			str2[strlen(str2) - 2] = '\0';	
		}

		strncpy(CCCD1, str2, 12);
		strncpy(CCCD2, str2 + 13, 12);
		strcpy(day, str2 + 26);

		int key1 = get_vertex_key_by_CCCD(g, CCCD1);
		int key2 = get_vertex_key_by_CCCD(g, CCCD2);

		add_edge(g, key1, key2, day);
	}

	fclose(fp2);
}

int main() {
	Graph g;

	int Case;
	while (1) {
		printf("---------------------------------\n");
		printf("1. Doc du lieu tu cac tep van ban\n");
		printf("2. Dang ky mot cong dan moi\n");
		printf("3. Ghi nhan tiep xuc\n");
		printf("4.\n");
		printf("5.\n");
		printf("6.\n");
		printf("7. Thoat chuong trinh\n");
		printf("---------------------------------\n");

		printf("Lua chon: ");
		scanf("%d", &Case);

		if (Case == 1) {
			g = create_graph();
			read_input_file(g);
		}

		if (Case == 2) {
			char CCCD[15], phoneNumber[15], name[70];

			printf("CCCD: "); scanf("%s", CCCD);
			printf("So dien thoai: "); scanf("%s", phoneNumber);
			printf("Ho va ten: "); scanf("%s", name);
			
			update_vertex(g, CCCD, phoneNumber, name);
		}

		if (Case == 3) {
			char CCCD1[15], CCCD2[15], day[15];

			while (1) {
				printf("CCCD nguoi thu 1: "); scanf("%s", CCCD1);
				printf("CCCD nguoi thu 2: "); scanf("%s", CCCD2);
				printf("Thoi gian tiep xuc: "); scanf("%s", day);
				//CCCD1[strlen(CCCD1) - 1] = '\0';
				//CCCD2[strlen(CCCD2) - 1] = '\0';
				//day[strlen(day) - 1] = '\0';

				if (get_vertex_key_by_CCCD(g, CCCD1) != -1 && get_vertex_key_by_CCCD(g, CCCD2) != -1) {
					break;
				} else {
					if (get_vertex_key_by_CCCD(g, CCCD1) == -1) {
						printf("CCCD %s khong ton tai trong co so du lieu!\n", CCCD1);
					}
					if (get_vertex_key_by_CCCD(g, CCCD2) == -1) {
						printf("CCCD %s khong ton tai trong co so du lieu!\n", CCCD2);
					}
					printf("Moi nhap lai!\n");
				}
			}

			int key1 = get_vertex_key_by_CCCD(g, CCCD1);
			int key2 = get_vertex_key_by_CCCD(g, CCCD2);

			update_edge(g, key1, key2, day);
		}

		if (Case == 7) {
			return 0;
		}
	}

	return 0;
}
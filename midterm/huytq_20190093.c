#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

void do_print();
void do_add(char *dn, char *ip);
void do_remove(char *dn);
void do_lookup_ip(char *dn);
void do_lookup_dn(char *ip);

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
    return 0;
  }

  if (strcmp(argv[1], "print") == 0) {
    if (argc != 2) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_print();
    return 0;
  }
  if (strcmp(argv[1], "add") == 0) {
    if (argc != 4) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_add(argv[2], argv[3]);
    return 0;
  }
  if (strcmp(argv[1], "remove") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_remove(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "ip") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_ip(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "dn") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_dn(argv[2]);
    return 0;
  }
  printf("Invalid parameters\n");
  return 0;
}

void print_entry(char *dn, char *ip) {
  printf("%s => %s\n", dn, ip);  
}

JRB read_input() {
    JRB cur = make_jrb();

    FILE *fp;
    fp = fopen("dns.txt", "r");

    int size = -1;
    fscanf(fp, "%d", &size);

    if (size == -1) {
        fclose(fp);
        return NULL;
    }

    char tmp_dn[300], tmp_ip[20];
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%s", tmp_dn);
        fscanf(fp, "%s", tmp_ip);

        jrb_insert_str(cur, strdup(tmp_dn), new_jval_s(strdup(tmp_ip)));
    }

    fclose(fp);

    return cur;
}

void save_to_file(JRB cur)
{
    FILE *fp;
    fp = fopen("dns.txt", "w");

    JRB node;

    int counter = 0;
    jrb_traverse(node, cur) {
        counter++;
    }
    fprintf(fp, "%d\n", counter);

    jrb_traverse(node, cur) {
        fprintf(fp, "%s\n", jval_s(node->key));
        fprintf(fp, "%s\n", jval_s(node->val));
    }

    fclose(fp);
}

void free_jrb_node(JRB node) {
    free(jval_s(node->key));
    free(jval_s(node->val));
}

void do_print() {
    JRB dns_ip = read_input();
    if (dns_ip == NULL) {
        printf("error\n");
        return;
    }

    JRB node;
    jrb_traverse(node, dns_ip) {
        print_entry(jval_s(node->key), jval_s(node->val));
    }
}

void do_add(char *dn, char *ip) {
    JRB dns_ip = read_input();
    if (dns_ip == NULL) {
        printf("error\n");
        return;
    }

    JRB node = jrb_find_str(dns_ip, dn);

    if (node == NULL) {
        jrb_insert_str(dns_ip, strdup(dn), new_jval_s(strdup(ip)));
    } else {
        free_jrb_node(node);
        jrb_delete_node(node);
        jrb_insert_str(dns_ip, strdup(dn), new_jval_s(strdup(ip)));
    }

    save_to_file(dns_ip);

    do_print();
}

void do_remove(char *dn) {
    JRB dns_ip = read_input();
    if (dns_ip == NULL) {
        printf("error\n");
        return;
    }

    JRB node = jrb_find_str(dns_ip, dn);

    if (node != NULL) {
        free_jrb_node(node);
        jrb_delete_node(node);
    }

    save_to_file(dns_ip);

    do_print();
}

void do_lookup_ip(char *dn) {
    JRB dns_ip = read_input();
    if (dns_ip == NULL) {
        printf("error\n");
        return;
    }

    JRB node = jrb_find_str(dns_ip, dn);

    if (node == NULL) {
        printf("not found\n");
    } else {
        print_entry(jval_s(node->key), jval_s(node->val));
    }
}

void do_lookup_dn(char *ip) {
    JRB dns_ip = read_input();
    if (dns_ip == NULL) {
        printf("error\n");
        return;
    }

    JRB result = make_jrb();
    int check = 0;

    JRB node;

    jrb_traverse(node, dns_ip) {
        if (strcmp(jval_s(node->val), ip) == 0) {
            jrb_insert_str(result, strdup(jval_s(node->key)), new_jval_i(1));
            check = 1;
        }
    }

    if (check == 1) {
        jrb_traverse(node, result) {
            print_entry(jval_s(node->key), ip);
        }
    } else {
        printf("not found\n");
    }
}

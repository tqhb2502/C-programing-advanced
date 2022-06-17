#include <stdio.h>
#include "symtab.h"
#include <stdlib.h>
#include <string.h>

Entry make_node_pb(void *name, void *number)
{
  Entry res;
  res.key = strdup((char *)name);
  res.value = malloc(sizeof(long));
  memcpy(res.value, number, sizeof(long));
  return res;
}

int compare_pb(void *name1, void *name2)
{
  return strcmp((char *)name1, (char *)name2);
}

int main()
{
    SymbolTable pb = create_symbol_table(make_node_pb, compare_pb);
    char *test_key = "Tran Quang Huy";
    long test_number = 123456;
    add_entry(test_key, &test_number, &pb);
    Entry *res = get_entry(test_key, &pb);
    if (res == NULL)
        printf("Khong tim thay!\n");
    else
        printf("%s: %ld\n", (char *)res->key, *((long *)res->value));
    return 0;
}
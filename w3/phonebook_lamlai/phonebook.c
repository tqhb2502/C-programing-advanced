#include <stdlib.h>
#include "phonebook.h"
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

PhoneBook createPhoneBook() {
  return create_symbol_table(make_node_pb, compare_pb);
}

void dropPhoneBook(PhoneBook* book) {
  drop_symbol_table(book);
  return;
}

void addPhoneNumber(char *name, long number, PhoneBook* book) {
  add_entry(name, &number, book);
  return;
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook book) {
  return get_entry(name, &book);
}

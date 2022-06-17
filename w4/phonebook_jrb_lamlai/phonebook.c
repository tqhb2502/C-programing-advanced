#include <stdlib.h>
#include "phonebook.h"
#include <string.h>
#include "jval.h"

void free_key_value_pb(Jval name, Jval number)
{
  char *str = name.s;
  free(str);
  return;
}

int compare_pb(Jval name1, Jval name2)
{
  return strcmp(name1.s, name2.s);
}

PhoneBook createPhoneBook() {
  return create_symbol_table(free_key_value_pb, compare_pb);
}

void dropPhoneBook(PhoneBook *book) {
  drop_symbol_table(book);
  return;
}

void addPhoneNumber(char *name, long number, PhoneBook *book) {
  add_entry(new_jval_s(strdup(name)), new_jval_l(number), book);
  return;
}

long getPhoneNumber(char *name, PhoneBook book) {
  Jval res = get_entry(new_jval_s(strdup(name)), &book);
  if (jval_v(res) == NULL)
    return -1;
  return res.l;
}

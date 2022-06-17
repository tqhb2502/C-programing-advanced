#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

PhoneBook createPhoneBook() {
  BTA *btfile;
  btinit();
  btfile = btcrt("pb_file", 0, 0);
  return btfile;
}

/*void dropPhoneBook(PhoneBook *book) {
  drop_symbol_table(book);
  return;
}*/

void closePhoneBook(PhoneBook book) {
  btcls(book);
  return;
}

void addPhoneNumber(char *name, long number, PhoneBook book) {
  binsky(book, name, (BTint)number);
  return;
}

long getPhoneNumber(char *name, PhoneBook book) {
  BTint res;
  if (bfndky(book, name, &res) != 0)
    res = -1;
  return (long)res;
}

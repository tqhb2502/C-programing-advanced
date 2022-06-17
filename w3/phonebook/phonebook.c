#include <stdlib.h>
#include "phonebook.h"
#include <string.h>

PhoneBook createPhoneBook() {
  PhoneBook cur;
  cur.entries = (PhoneEntry *)malloc(INITIAL_SIZE * sizeof(PhoneEntry));
  cur.total = 0;
  cur.size = INITIAL_SIZE;
  return cur;
}

void dropPhoneBook(PhoneBook* book) {
  free(book->entries);
  return;
}

void addPhoneNumber(char *name, long number, PhoneBook* book) {
  PhoneEntry *cur = getPhoneNumber(name, *book);
  if (cur == NULL)
  {
    /*if (book->total == book->size)
    {

    }*/
    strcpy((book->entries + book->total)->name, name);
    (book->entries + book->total)->number = number;
    book->total++;
  }
  else cur->number = number;
  return;
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook book) {
  for (int i = 0; i < book.total; i++)
    if (strcmp((book.entries + i)->name, name) == 0)
      return (book.entries + i);
  return NULL;
}

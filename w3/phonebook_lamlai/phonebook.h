#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include "symtab.h"

typedef Entry PhoneEntry;

typedef SymbolTable PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook *book);

void addPhoneNumber(char *name, long number, PhoneBook *book);
PhoneEntry *getPhoneNumber(char *name, PhoneBook book);

#endif

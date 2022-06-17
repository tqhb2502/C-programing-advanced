#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include "btree.h"

typedef BTA* PhoneBook;

PhoneBook createPhoneBook();
//void dropPhoneBook(PhoneBook book);
void closePhoneBook(PhoneBook book);

void addPhoneNumber(char *name, long number, PhoneBook book);
long getPhoneNumber(char *name, PhoneBook book);

#endif

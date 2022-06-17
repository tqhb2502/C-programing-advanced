#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "btree.h"

typedef BTA* Dictionary;

Dictionary createDictionary(char *);
Dictionary openDictionary(char *);
int closeDictionary(Dictionary);
int addWord(Dictionary, char *, char *);
int searchWord(Dictionary, char *, char *);
int deleteWord(Dictionary, char *);
int modifyMeaning(Dictionary, char *, char *);
int printDictionary(Dictionary);
int importEngLat(Dictionary, char *, int *);

#define MAX_WORD_SIZE 1024
#define MAX_MEANING_SIZE 1024

#define WNEXIST 1 //word doesn't exist
#define WEXIST 2 //word already exists
#define CNOFILE 3 //can not open file

#endif
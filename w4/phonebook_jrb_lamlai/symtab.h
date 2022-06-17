#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include "jrb.h"

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct
{
    JRB entries;
    void (*free_key_value)(Jval, Jval);
    int (*compare)(Jval, Jval);
} SymbolTable;

SymbolTable create_symbol_table(void (*free_key_value)(Jval, Jval), int (*compare)(Jval, Jval));

void drop_symbol_table(SymbolTable *tab);

void add_entry(Jval key, Jval value, SymbolTable *tab);

Jval get_entry(Jval key, SymbolTable *tab);

#endif
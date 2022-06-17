#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct
{
    void *key;
    void *value;
} Entry;

typedef struct
{
    Entry *entries;
    int total, size;
    Entry (*make_node)(void *, void *);
    int (*compare)(void *, void *);
} SymbolTable;

SymbolTable create_symbol_table(Entry (*make_node)(void *, void *), int (*compare)(void *, void *));

void drop_symbol_table(SymbolTable *tab);

void add_entry(void *key, void *value, SymbolTable *tab);

Entry *get_entry(void *key, SymbolTable *tab);

#endif
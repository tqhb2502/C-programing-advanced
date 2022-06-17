#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"
#include "jval.h"

SymbolTable create_symbol_table(void (*free_key_value)(Jval, Jval), int (*compare)(Jval, Jval))
{
    SymbolTable tab;
    tab.entries = make_jrb();
    tab.free_key_value = free_key_value;
    tab.compare = compare;
    return tab;
}

void drop_symbol_table(SymbolTable *tab)
{
    JRB i;
    jrb_traverse(i, tab->entries)
    {
        tab->free_key_value(i->key, i->val);
    }
    jrb_free_tree(tab->entries);
    return;
}

Jval get_entry(Jval key, SymbolTable *tab)
{
    JRB res;
    res = jrb_find_gen(tab->entries, key, tab->compare);
    if (res == NULL)
        return new_jval_v(NULL);
    return res->val;
}

void add_entry(Jval key, Jval value, SymbolTable *tab)
{
    JRB res = jrb_find_gen(tab->entries, key, tab->compare);
    if (res != NULL)
    {
        tab->free_key_value(res->key, res->val);
        jrb_delete_node(res);
    }
    jrb_insert_gen(tab->entries, key, value, tab->compare);
    return;
}
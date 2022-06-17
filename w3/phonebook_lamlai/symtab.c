#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

SymbolTable create_symbol_table(Entry (*make_node)(void *, void *), int (*compare)(void *, void*))
{
    SymbolTable tab;
    tab.entries = (Entry *)malloc(INITIAL_SIZE * sizeof(Entry));
    tab.total = 0;
    tab.size = INITIAL_SIZE;
    tab.make_node = make_node;
    tab.compare = compare;
    return tab;
}

void drop_symbol_table(SymbolTable *tab)
{
    for (int i = 0; i < tab->total; i++)
    {
        free(tab->entries->key);
        free(tab->entries->value);
    }
    return;
}

Entry *get_entry(void *key, SymbolTable *tab)
{
    for (int i = 0; i < tab->total; i++)
        if (tab->compare((tab->entries + i)->key, key) == 0)
            return (tab->entries + i);
    return NULL;
}

void add_entry(void *key, void *value, SymbolTable *tab)
{
    Entry *cur = get_entry(key, tab);
    if (cur != NULL)
    {
        Entry new = tab->make_node(cur->key, value);
        free(cur->key);
        free(cur->value);
        cur = &new;
    }
    else
    {
        if (tab->total == tab->size)
        {
            Entry *new = (Entry *)malloc((tab->size + INCREMENTAL_SIZE) * sizeof(Entry));
            for (int i = 0; i < tab->total; i++)
            {
                new[i] = tab->make_node((tab->entries+ i)->key, (tab->entries + i)->value);
                free((tab->entries + i)->key);
                free((tab->entries + i)->value);
            }
            tab->entries = new;
        }
        tab->entries[tab->total] = tab->make_node(key, value);
        tab->total++;
    }
    return;
}
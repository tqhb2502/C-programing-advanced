#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

#include "weighted_graph.h"

typedef struct
{
    Graph graph;
    JRB root;
} HuffmanTree;

typedef struct
{
    int size;
    char bit[100];
} HuffmanTable;

HuffmanTree makeHuffmanTree(char *, int, HuffmanTable *);
void compress(char *, int, HuffmanTable *, char *, int *);

#endif
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include "weighted_graph.h"

typedef struct {
    Graph graph;
    JRB root;
} HuffmanTree;

typedef struct {
    int size;
    char bits[9];
} Coding;

HuffmanTree makeHuffman(char *, int);
void createHuffmanTable(HuffmanTree, Coding *);
void compress(char *, int, char *, int *, Coding *);

#endif
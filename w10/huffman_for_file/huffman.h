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

typedef struct {
    int size;
    int *node;
} HuffmanTreeArray;

HuffmanTree makeHuffman(FILE *);
void createHuffmanTable(HuffmanTree, Coding *);
HuffmanTreeArray tree2array(HuffmanTree);
void compressFile(FILE *, FILE *);
void decompressFile(FILE *, FILE *);

#endif
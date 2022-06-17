#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman_tree.h"

HuffmanTree createHuffmanTree()
{
    HuffmanTree tree;
    tree.graph = createGraph();
    tree.root = make_jrb();
    return tree;
}

int getAppear(char *str, int *appearCounter)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
        sum = sum + appearCounter[i];
    return sum;
}

Dllist getMin(Dllist pqueue, int *appearCounter)
{
    int min = INFINITIVE_VALUE, cur;
    Dllist pqueueNode, result;
    JRB treeNode;
    dll_traverse(pqueueNode, pqueue)
    {
        treeNode = (JRB)jval_v(pqueueNode->val);
        cur = getAppear(jval_s(treeNode->val), appearCounter);
        if (min > cur)
        {
            min = cur;
            result = pqueueNode;
        }
    }
    return result;
}

int dllHasOneNode(Dllist pqueue)
{
    int count = 0;
    Dllist pqueueNode;
    dll_traverse(pqueueNode, pqueue)
        count++;
    return (count == 1);
}

void addBit0(HuffmanTable *table, char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        table[str[i]].bit[table[str[i]].size] = '0';
        table[str[i]].size++;
    }
    return;
}

void addBit1(HuffmanTable *table, char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        table[str[i]].bit[table[str[i]].size] = '1';
        table[str[i]].size++;
    }
    return;
}

HuffmanTree makeHuffmanTree(char *buffer, int size, HuffmanTable *table)
{
    int appearCounter[256];
    for (int i = 0; i < 256; i++)
        appearCounter[i] = 0;
    for (int i = 0; i < size; i++)
        appearCounter[buffer[i]]++;

    HuffmanTree tree = createHuffmanTree();
    Dllist pqueue = new_dllist(), pqueueNode;
    char str[1];
    int idCounter = 0;
    for (int i = 0; i < 256; i++)
        if (appearCounter[i] != 0)
        {
            str[0] = (char)i;
            addVertex(tree.graph, idCounter, str);
            dll_append(pqueue, new_jval_v(getVertex(tree.graph, idCounter)));
            idCounter++;
        }
    
    JRB treeNode1, treeNode2;
    char str2[100];
    while (!dllHasOneNode(pqueue))
    {
        pqueueNode = getMin(pqueue, appearCounter);
        treeNode1 = (JRB)jval_v(pqueueNode->val);
        dll_delete_node(pqueueNode);

        pqueueNode = getMin(pqueue, appearCounter);
        treeNode2 = (JRB)jval_v(pqueueNode->val);
        dll_delete_node(pqueueNode);

        strcpy(str2, jval_s(treeNode1->val));
        strcat(str2, jval_s(treeNode2->val));

        addVertex(tree.graph, idCounter, str2);
        addEdge(tree.graph, idCounter, jval_i(treeNode1->key), 0);
        addBit0(table, jval_s(treeNode1->val));
        addEdge(tree.graph, idCounter, jval_i(treeNode2->key), 1);
        addBit1(table, jval_s(treeNode2->val));

        dll_append(pqueue, new_jval_v(getVertex(tree.graph, idCounter)));

        idCounter++;
    }

    pqueueNode = dll_first(pqueue);
    tree.root = (JRB)jval_v(pqueueNode->val);

    return tree;
}

void addHuffmanChar(char ch, HuffmanTable *table, char *huffman, int *nbit)
{
    for (int i = table[ch].size - 1; i >= 0; i--)
    {
        huffman[*nbit] = table[ch].bit[i];
        (*nbit)++;
    }
    return;
}

void compress(char *buffer, int size, HuffmanTable *table, char *huffman, int *nbit)
{
    for (int i = 0; i < size; i++)
        addHuffmanChar(buffer[i], table, huffman, nbit);
    return;
}
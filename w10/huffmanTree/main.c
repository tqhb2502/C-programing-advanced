#include <stdlib.h>
#include <stdio.h>
#include "huffman_tree.h"

int main()
{
    HuffmanTable table[256];
    for (int i = 0; i < 256; i++)
        table[i].size = 0;
    HuffmanTree tree = makeHuffmanTree("abcdeff", 7, table);
    //BFS(tree.graph, jval_i(tree.root->key), -1);
    for (int i = 0; i < 256; i++)
        if (table[i].size != 0)
        {
            printf("%c ", i);
            for (int j = table[i].size - 1; j >= 0; j--)
                printf("%c", table[i].bit[j]);
            printf("\n");
        }
    char result[25600];
    int nbit;
    compress("abcdeff", 7, table, result, &nbit);
    printf("%d\n%s\n", nbit, result);
    return 0;
}
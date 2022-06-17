#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main() {
    // tạo cây huffman
    HuffmanTree htree = makeHuffman("Eerie eyes seen near lake.", 26);
    //BFS(htree.graph, jval_i(htree.root->key), -1);

    // tạo bảng huffman
    Coding htable[256];
    for (int i = 0; i <= 255; i++) {
        htable[i].size = 0;
    }
    createHuffmanTable(htree, htable);
    /*for (int i = 0; i <= 255; i++) {
        if (htable[i].size > 0) {
            printf("*%c* %s\n", i, htable[i].bits);
        }
    }*/

    // nén xâu
    char huffman[8000];
    int nbit = 0;
    compress("Eerie eyes seen near lake.", 26, huffman, &nbit, htable);
    huffman[nbit] = '\0';
    printf("%s\n", huffman);
    return 0;
}
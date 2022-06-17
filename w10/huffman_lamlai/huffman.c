#include <stdlib.h>
#include <string.h>
#include "huffman.h"

// kiểm tra pqueue còn 1 phần tử
int hasOneNode(Dllist list) {
    int counter = 0;

    Dllist node;
    dll_traverse(node, list) {
        counter++;
    }

    return (counter == 1) ? 1 : 0;
}

// đếm tổng số lần các kí tự (ứng với nút trên cây) xuất hiện
int countAppear(JRB treeNode, int *appear) {
    int counter = 0;

    char *tmp_string = jval_s(treeNode->val);
    for (int i = 0; i < strlen(tmp_string); i++) {
        counter += appear[tmp_string[i]];
    }

    return counter;
}

// tìm phần tử có khóa nhỏ nhất trong pqueue
Dllist pqueueGetMin(Dllist pqueue, int *appear) {
    int minAppear = INFINITIVE_VALUE;

    Dllist node, minNode;
    JRB treeNode;
    int cur;
    dll_traverse(node, pqueue) {
        treeNode = (JRB) jval_v(node->val);
        cur = countAppear(treeNode, appear);
        if (cur < minAppear) {
            minAppear = cur;
            minNode = node;
        }
    }

    return minNode;
}

// tạo cây Huffman
HuffmanTree makeHuffman(char *buffer, int size) {
    // tạo cây
    HuffmanTree newHuffmanTree;
    newHuffmanTree.graph = createGraph();

    // đếm số lần xuất hiện của mỗi ký tự trong xâu buffer
    int appear[256];
    for (int i = 0; i <= 255; i++) {
        appear[i] = 0;
    }
    for (int i = 0; i < strlen(buffer); i++) {
        appear[buffer[i]]++;
    }

    // kí tự nào xuất hiện thì tạo nút của ký tự đó trong cây, thêm nút vào pqueue
    Dllist pqueue = new_dllist();
    int idCounter = 0;
    char tmp_string[2];
    for (int i = 0; i <= 255; i++) {
        if (appear[i] > 0) {
            tmp_string[0] = (char) i;
            tmp_string[1] = '\0';
            addVertex(newHuffmanTree.graph, idCounter, tmp_string);

            dll_append(pqueue, new_jval_v(getVertex(newHuffmanTree.graph, idCounter)));

            idCounter++;
        }
    }

    // ghép cây
    char tmp_string_2[257];
    Dllist minNode_1, minNode_2;
    JRB u, v, parent;
    while (!hasOneNode(pqueue)) {
        // lấy 2 nút có tổng số lần xuất hiện các ký tự ít nhất
        minNode_1 = pqueueGetMin(pqueue, appear);
        u = (JRB) jval_v(minNode_1->val);
        dll_delete_node(minNode_1);
        minNode_2 = pqueueGetMin(pqueue, appear);
        v = (JRB) jval_v(minNode_2->val);
        dll_delete_node(minNode_2);

        // tạo nút cha cho 2 nút trên
        strcpy(tmp_string_2, jval_s(u->val));
        strcat(tmp_string_2, jval_s(v->val));
        addVertex(newHuffmanTree.graph, idCounter, tmp_string_2);

        // tạo cạch nối cha-con
        parent = getVertex(newHuffmanTree.graph, idCounter);
        addEdge(newHuffmanTree.graph, jval_i(parent->key), jval_i(u->key), 0);
        addEdge(newHuffmanTree.graph, jval_i(parent->key), jval_i(v->key), 1);

        // thêm cha vào pqueue
        dll_append(pqueue, new_jval_v(parent));

        idCounter++;
    }

    // gán root của cây là phần tử cuối cùng còn lại trong pqueue
    newHuffmanTree.root = (JRB) jval_v(dll_first(pqueue)->val);

    return newHuffmanTree;
}

// thăm cây Huffman đã tạo ở trên để cho ra HuffmanTable
void treeTraverse(Graph g, JRB curNode, char *bitSequence, int bitSize, Coding *htable) {
    JRB node = jrb_find_int(g.edges, jval_i(curNode->key));
    if (node != NULL) {
        // nếu nút đang thăm không phải nút lá, thăm các con của nó
        JRB adj_list = (JRB) jval_v(node->val);

        jrb_traverse(node, adj_list) {
            // lấy key nút con, và trọng số cạnh nối
            int key = jval_i(node->key);
            int w = (int) jval_d(node->val);
            
            // nếu trọng số là 1, thêm bit 1, ngược lại, thêm bit 0
            if (w == 1) {
                bitSequence[bitSize] = '1';
            } else {
                bitSequence[bitSize] = '0';
            }
            bitSize++;

            // thăm nút con
            JRB nextNode = getVertex(g, key);
            treeTraverse(g, nextNode, bitSequence, bitSize, htable);

            // thăm xong nút con, xóa bỏ bit ở cạnh nối cha-con đã thêm ở trên
            bitSize--;
        }
    } else {
        // nếu nút đang thăm là nút lá, thêm ký tự của nút này vào HuffmanTable
        char *tmp_string = jval_s(curNode->val);
        char ch = tmp_string[0];
        htable[ch].size = bitSize;

        for (int i = 0; i < bitSize; i++) {
            htable[ch].bits[i] = bitSequence[i];
        }
        htable[ch].bits[bitSize] = '\0';
    }
    return;
}

// tạo HuffmanTable(bảng chuyển từ ký tự sang bit)
void createHuffmanTable(HuffmanTree htree, Coding *htable) {
    char bitSequence[9];
    treeTraverse(htree.graph, htree.root, bitSequence, 0, htable);
    return;
}

// nén ký tự ch
void addHuffmanChar(char ch, Coding *htable, char *huffman, int *nbit) {
    for (int i = 0; i < htable[ch].size; i++) {
        huffman[*nbit] = htable[ch].bits[i];
        (*nbit)++;
    }
    return;
}

// nén xâu buffer
void compress(char *buffer, int size, char *huffman, int *nbit, Coding *htable) {
    for (int i = 0; i < size; i++) {
        addHuffmanChar(buffer[i], htable, huffman, nbit);
    }
    return;
}
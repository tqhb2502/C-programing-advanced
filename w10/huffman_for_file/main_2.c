/**
 * giải nén file
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char *argv[]) {
    // xử lý tên file
    char *input_filename, *output_filename;
    if (argc == 3) {
        input_filename = argv[1];

        output_filename = argv[2];
    } else if (argc == 2) {
        input_filename = argv[1];

        output_filename = (char *) malloc(strlen(argv[1]) + 7);
        strcpy(output_filename, input_filename);
        strcat(output_filename, "_decom");
    } else {
        printf("Can't detect file to compress!\n");
        exit(0);
    }
    /*printf("%s\n", input_filename);
    printf("%s\n", output_filename);
    printf("OK\n");*/

    // giải nén file in thành file out
    FILE *in, *out;
    in = fopen(input_filename, "r");
    out = fopen(output_filename, "w");

    decompressFile(in, out);

    fclose(in);
    fclose(out);
    return 0;
}
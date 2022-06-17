#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("text.txt", "r");
    int number;
    char str[100];
    while (!feof(fp))
    {
        fgetc(fp);
        fscanf(fp, "%d", &number);
        fgets(str, 100, fp);
        printf("%d\n", number);
        fputs(str, stdout);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
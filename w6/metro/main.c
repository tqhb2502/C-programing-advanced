#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

typedef struct Station_t
{
    int number;
    char name[100];
    struct Station_t *next;
} Station;

typedef struct Station_list_t
{
    Station *head;
} Station_list;

void list_add(Station_list *list, int number, char *name)
{
    Station *cur = (Station *)malloc(sizeof(Station));
    cur->number = number;
    strcpy(cur->name, name);
    if (list->head == NULL)
        list->head = cur;
    else
    {
        Station *tmp = list->head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = cur;
    }
    return;
}

Station *list_find_by_number(Station_list *list, int number)
{
    Station *tmp = list->head;
    while (tmp != NULL)
    {
        if (tmp->number == number)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

Station *list_find_by_name(Station_list *list, char *name)
{
    Station *tmp = list->head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void read_input_file(char *filename, Station_list *list, Graph graph)
{
    FILE *fp;
    fp = fopen(filename, "r");
    char str[100];
    int prenumber, number;
    char name[100];
    int mode = -1, i, j;
    while (!feof(fp))
    {
        fgets(str, 100, fp);
        if (!feof(fp))
            str[strlen(str) - 2] = '\0';
        if (strcmp(str, "[STATIONS]") == 0)
        {
            mode = 0;
            continue;
        }
        if (strcmp(str, "[LINES]") == 0)
        {
            mode = 1;
            continue;
        }
        if (mode == 0)
        {
            number = 0;
            i = 1;
            while ('0' <= str[i] && str[i] <= '9')
            {
                number = number * 10 + (str[i] - 48);
                i++;
            }
            i++;
            strcpy(name, str + i);
            list_add(list, number, name);
        }
        if (mode == 1)
        {
            number = -1;
            for (i = 0; i < strlen(str); i++)
                if (str[i] == 'S')
                {
                    j = i + 1;
                    prenumber = number;
                    number = 0;
                    while ('0' <= str[j] && str[j] <= '9')
                    {
                        number = number * 10 + (str[j] - 48);
                        j++;
                    }
                    if (prenumber != -1 && number != -1)
                        addEdge(graph, prenumber, number);
                }
        }
    }
    fclose(fp);
    return;
}

int main()
{
    Station_list *list = (Station_list *)malloc(sizeof(Station_list));
    Graph graph = createGraph();
    read_input_file("metro_line", list, graph);
    char name[100];
    int output[100], i;
    printf("Enter the name of the station: ");
    fgets(name, 99, stdin);
    name[strlen(name) - 1] = '\0';
    Station *cur, *tmp;
    cur = list_find_by_name(list, name);
    int total = getAdjacentVertices(graph, cur->number, output);
    printf("Adjacent station(s):\n");
    for (i = 0; i < total; i++)
    {
        tmp = list_find_by_number(list, output[i]);
        fputs(tmp->name, stdout);
        printf("\n");
    }
    return 0;
}
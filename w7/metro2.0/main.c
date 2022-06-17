#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

void clearBuffer()
{
    while ((getchar()) != '\n');
    return;
}

typedef struct Station_t
{
    int number;
    char name[100];
} Station;

void list_add(Dllist list, int number, char *name)
{
    Station *cur = (Station *)malloc(sizeof(Station));
    cur->number = number;
    strcpy(cur->name, name);
    dll_append(list, new_jval_v(cur));
    return;
}

Station *list_find_by_number(Dllist list, int number)
{
    Dllist tmp;
    Station *cur;
    dll_traverse(tmp, list)
    {
        cur = (Station *)tmp->val.v;
        if (cur->number == number) return cur;
    }
    return NULL;
}

Station *list_find_by_name(Dllist list, char *name)
{
    Dllist tmp;
    Station *cur;
    dll_traverse(tmp, list)
    {
        cur = (Station *)tmp->val.v;
        if (strcmp(cur->name, name) == 0) return cur;
    }
    return NULL;
}

int read_input_file(char *filename, Dllist list, Graph graph)
{
    int station_counter = 0;
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
            station_counter++;
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
    return station_counter;
}

int path_exist(int a, int b, int *parent, int *output)
{
    int counter = 0;
    output[counter] = b;
    counter++;
    while (b != -1)
    {
        if (a == b) return counter;
        b = parent[b];
        output[counter] = b;
        counter++;
    }
    return 0;
}

int main()
{
    Dllist list = new_dllist();
    Graph graph = createGraph();
    int option;
    char name[100];
    int output[100], station_total, parent[100];
    while (1)
    {
        printf("==============Options==============\n");
        printf("1. Read metro lines file\n");
        printf("2. Print adjacent vertices\n");
        printf("3. Metro lines is connected?\n");
        printf("4. Find shortest path\n");
        printf("5. Quit\n");
        printf("===================================\n");
        scanf("%d", &option);
        if (option == 1)
        {
            station_total = read_input_file("metro_line", list, graph);
            printf("Successfully imported %d station(s)!\n", station_total);
        }
        if (option == 2)
        {
            clearBuffer();
            printf("Enter station's name: ");
            fgets(name, 99, stdin);
            name[strlen(name) - 1] = '\0';
            Station *cur, *tmp;
            cur = list_find_by_name(list, name);
            int total = getAdjacentVertices(graph, cur->number, output);
            printf("Adjacent station(s):\n");
            for (int i = 0; i < total; i++)
            {
                tmp = list_find_by_number(list, output[i]);
                fputs(tmp->name, stdout);
                printf("\n");
            }
        }
        if (option == 3)
        {
            int visited_vertices = DFS(graph, 1, -1);
            if (visited_vertices == station_total)
                printf("YES\n");
            else
                printf("NO\n");
        }
        if (option == 4)
        {
            for (int i = 1; i <= station_total; i++)
                parent[i] = -1;
            Station *u, *v;
            clearBuffer();
            printf("Start: ");
            fgets(name, 99, stdin);
            name[strlen(name) - 1] = '\0';
            u = list_find_by_name(list, name);
            printf("Destination: ");
            fgets(name, 99, stdin);
            name[strlen(name) - 1] = '\0';
            v = list_find_by_name(list, name);
            BFS(graph, u->number, v->number, parent);
            int result = path_exist(u->number, v->number, parent, output);
            if (result == 0)
                printf("There is no path between 2 given stations!\n");
            else
            {
                printf("Shortest path:\n");
                Station *tmp;
                for (int i = result - 1; i >= 0; i--)
                {
                    tmp = list_find_by_number(list, output[i]);
                    fputs(tmp->name, stdout);
                    printf("\n");
                }
            }
        }
        if (option == 5)
        {
            printf("Success!\n");
            break;
        }
    }
    /*Dllist list_node;
    Station *cur;
    dll_traverse(list_node, list)
    {
        cur = (Station *)list_node->val.v;
        printf("%d: ", cur->number);
        fputs(cur->name, stdout);
        printf("\n");
    }*/
    return 0;
}
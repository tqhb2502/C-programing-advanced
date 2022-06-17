#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "directed_graph.h"

int makeClass(Graph g, JRB classID, char *className, int *cur)
{
    JRB node = jrb_find_str(classID, className);
    if (node == NULL)
    {
        (*cur)++;
        jrb_insert_str(classID, strdup(className), new_jval_i(*cur));
        addVertex(g, *cur, className);
        return (*cur);
    }
    return node->val.i;
}

void readInputFile(char *filename, Graph g, JRB classID)
{
    FILE *fp;
    char str[10];
    int count = 0;
    int curClass, prereqClass;
    fp = fopen(filename, "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s", str);
        if (strcmp(str, "CLASS") == 0)
        {
            fscanf(fp, "%s", str);
            curClass = makeClass(g, classID, str, &count);
        }
        if (strcmp(str, "PREREQ") == 0)
        {
            fscanf(fp, "%s", str);
            prereqClass = makeClass(g, classID, str, &count);
            addEdge(g, prereqClass, curClass);
        }
    }
    fclose(fp);
    return;
}

void printGraph(Graph g)
{
    JRB node;
    jrb_traverse(node, g.vertices)
        printf("%d: %s\n", node->key.i, node->val.s);
    return;
}

int main()
{
    JRB classID = make_jrb();
    Graph g = createGraph();
    readInputFile("input_file", g, classID);
    /*addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
    addEdge(g, 0, 1); addEdge(g, 0, 2);
    addEdge(g, 1, 3); addEdge(g, 5, 4); addEdge(g, 3, 4);*/
    if (!DAG(g))
    {
        printf("Can not make topological sort\n");
        return 0;
    }
    int output[100], n = 0;
    topoSort(g, output, &n);
    printf("The topological order:\n");
    for (int i=0; i<n; i++)
        printf("%s\n", getVertex(g, output[i]));
    return 0;
}
// Brian Pereira Alegria
// brpereir
// FindPath.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int v1, v2;
    char line[MAX_LEN];

    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    fgets(line, MAX_LEN, in);
    Graph Graph = newGraph(atoi(line));
    v1 = 0;
    v2 = 0;

    while (fgets(line, MAX_LEN, in) != NULL)
    {
        sscanf(line, "%d %d", &v1, &v2);

        if (v1 != 0 || v2 != 0)
        {
            addEdge(Graph, v1, v2);
        }
        else
            break;
    }
    printGraph(out, Graph);
    fprintf(out, "\n");

    while (fgets(line, MAX_LEN, in) != NULL)
    {
        sscanf(line, "%d %d", &v1, &v2);
        if (v1 != 0 || v2 != 0)
        {
            BFS(Graph, v1);
            fprintf(out, "\nThe distance from %d to %d is ", v1, v2);
            if (getDist(Graph, v2) == INF)
            {
                fprintf(out, "infinity\n");
            }
            else
            {
                fprintf(out, "%d\n", getDist(Graph, v2));
            }
            List A = newList();
            getPath(A, Graph, v2);
            if (front(A) != NIL)
            {
                fprintf(out, "A shortest %d-%d path is: ", v1, v2);
                printList(out, A);
                fprintf(out, "\n");
            }
            else
            {
                fprintf(out, "No %d-%d path exists\n", v1, v2);
            }
            freeList(&A);
        }
        else
            break;
    }

    fclose(in);
    fclose(out);
    freeGraph(&Graph);

    return (0);
}

// Brian Pereira Alegria
// brpereir
// FindComponents.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int v1, v2, n, k;
    int NC, SC;
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
    n = atoi(line);
    List S = newList();

    k = 1;
    while (k <= n)
    {
        append(S, k);
        k++;
    }

    Graph G = newGraph(n);
    Graph Gt = newGraph(n);
    v1 = 0;
    v2 = 0;

    while (fgets(line, MAX_LEN, in) != NULL)
    {
        sscanf(line, "%d %d", &v1, &v2);
        if (v1 != 0 || v2 != 0)
        {
            addArc(G, v1, v2);
        }
        else
            break;
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    NC = 0;
    Gt = transpose(G);
    DFS(G, S);
    DFS(Gt, S);

    for (moveBack(S); index(S) != UNDEF; movePrev(S))
    {
        if (getParent(Gt, get(S)) == NIL)
        {
            NC++;
        }
    }

    List *C = calloc(NC + 1, sizeof(List));
    fprintf(out, "G contains %d strongly connected components:\n", NC);

    k = 1;
    while (k <= NC)
    {
        C[k] = newList();
        k++;
    }

    SC = 1;
    for (moveBack(S); index(S) != UNDEF; movePrev(S))
    {
        int m = get(S);
        prepend(C[SC], m);
        if (getParent(Gt, m) == NIL)
        {
            fprintf(out, "Component %d: ", SC);
            printList(out, C[SC]);
            fprintf(out, "\n");
            SC++;
        }
    }

    k = 1;
    while (k <= NC)
    {
        freeList(&C[k]);
        k++;
    }

    free(&(*C));
    freeList(&S);
    freeGraph(&G);
    freeGraph(&Gt);
    fclose(in);
    fclose(out);

    return (0);
}
// Brian Pereira Alegria
// brpereir
// Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj
{
    List *adj;
    int *C;
    int *D;
    int *P;
    int size;
    int order;
    int source;

} GraphObj;

Graph newGraph(int n)
{
    if (n < 1)
    {
        printf("Graph Error: calling newGraph() with invalid input\n");
        exit(EXIT_FAILURE);
    }
    Graph Graph = malloc(sizeof(GraphObj));
    Graph->adj = calloc(n + 1, sizeof(List));
    Graph->P = calloc(n + 1, sizeof(int));
    Graph->D = calloc(n + 1, sizeof(int));
    Graph->C = calloc(n + 1, sizeof(int));
    Graph->order = n;
    Graph->size = 0;
    Graph->source = NIL;
    int k = 1;
    while (k < (n + 1))
    {
        Graph->adj[k] = newList();
        Graph->C[k] = 0;
        Graph->D[k] = INF;
        Graph->P[k] = NIL;
        k++;
    }
    return Graph;
}

void freeGraph(Graph *pG)
{
    int k = 0;
    while (k <= (*pG)->order)
    {
        freeList(&(*pG)->adj[k]);
        k++;
    }
    free((*pG)->adj);
    free((*pG)->C);
    free((*pG)->D);
    free((*pG)->P);
    free(*pG);
}

int getSize(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call getSize() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G)
{

    if (G == NULL)
    {
        printf("Graph Error: cannot call getSource() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call getParent() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call getParent() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->P[u];
}

int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call getDist() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    if (!(u <= 1 || u <= getOrder(G)))
    {
        printf("Graph Error: cannot call getDist() with a invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL)
    {
        return INF;
    }
    return G->D[u];
}

void getPath(List L, Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call getPath() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    if (u > getOrder(G) || u < 1)
    {
        printf("Graph Error: cannot call getParent() with unreachable\n");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G))
    {
        append(L, u);
    }
    else if (getParent(G, u) == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

void makeNull(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call makeNull() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    int k = 1;
    while (k <= getOrder(G))
    {
        clear(G->adj[k]);
        k++;
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v)
{
    if (u > getOrder(G) || u < 1)
    {
        printf("Graph Error: cannot call addEdge() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(G) || v < 1)
    {
        printf("Graph Error: cannot call addEdge() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call addArc() on NULL reference \n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G))
    {
        printf("Graph Error: cannot call addArc() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G))
    {
        printf("Graph Error: cannot call addArc() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    List L = G->adj[u];
    moveFront(L);

    while (n == 0 && index(L) != -1)
    {
        if (get(L) > v)
        {
            insertBefore(L, v);
            n = 1;
        }
        else
        {
            moveNext(L);
        }
    }
    if (0 > index(L))
    {
        append(L, v);
    }
    G->size++;
}

void BFS(Graph G, int s)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call BFS() on null graph\n");
        exit(EXIT_FAILURE);
    }

    if (s < 1 || s > getOrder(G))
    {
        printf("Graph Error: cannot call BFS() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }

    int k = 1;
    while (k <= getOrder(G))
    {
        G->C[k] = 0;
        G->D[k] = INF;
        G->P[k] = NIL;
        k++;
    }

    G->source = s;
    G->C[s] = 1; //grey
    G->D[s] = 0;
    G->P[s] = NIL;

    List L = newList();

    append(L, s);

    while (length(L) > 0)
    {

        int i = front(L);
        List A = G->adj[i];
        deleteFront(L);

        for (moveFront(A); index(A) != -1; moveNext(A))
        {
            int n = get(A);

            if (G->C[n] == 0)
            {
                G->C[n] = 1;
                G->D[n] = G->D[i] + 1;
                G->P[n] = i;
                append(L, n);
            }
        }
        G->C[i] = 2;
    }
    freeList(&L);
}

void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: cannot call printGraph() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);   //Printing vertex label
        printList(out, G->adj[i]); //Printing adjacency List of vertex label
        fprintf(out, "\n");
    }
}
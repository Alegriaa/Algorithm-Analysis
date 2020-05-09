     // Brian Pereira Alegria
// brpereir
// Graph.c


#include <stdio.h>

#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj {
    List *adj;
    int *C;
    int *D;
    int *P;
    int *F;
    int size;
    int order;

} GraphObj;

Graph newGraph(int n) {
    if (n < 1) {
        printf("Graph Error: calling newGraph() with invalid input\n");
        exit(EXIT_FAILURE);
    }
    Graph Graph = malloc(sizeof(GraphObj));
    Graph->adj = calloc(n + 1, sizeof(List));
    Graph->P = calloc(n + 1, sizeof(int));
    Graph->D = calloc(n + 1, sizeof(int));
    Graph->C = calloc(n + 1, sizeof(int));
    Graph->F = calloc(n + 1, sizeof(int));
    Graph->order = n;
    Graph->size = 0;
    int k = 1;
    while (k < (n + 1)) {
        Graph->adj[k] = newList();
        Graph->C[k] = 0;
        Graph->D[k] = INF;
        Graph->P[k] = NIL;
        Graph->F[k] = UNDEF;
        k++;
    }
    return Graph;
}


void freeGraph(Graph *pG) {
    int k = 0;
    while (k <= (*pG)->order) {
        freeList(&(*pG)->adj[k]);
        k++;
    }
    free((*pG)->adj);
    free((*pG)->C);
    free((*pG)->D);
    free((*pG)->P);
    free((*pG)->F);
    free(*pG);
}


int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: cannot call getOrder() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: cannot call getSize() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}


int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: cannot call getParent() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: cannot call getParent() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->P[u];

}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: cannot call getDist() on NULL reference\n");
        exit(EXIT_FAILURE);
    }
    if (!(u <= 1 || u <= getOrder(G))) {
        printf("Graph Error: cannot call getDist() with a invalid vertex\n");
        exit(EXIT_FAILURE);
    }

    return G->D[u];
}

int getFinish(Graph G, int u) {
    if (!(u <= 1 || u <= getOrder(G))) {
        printf("Graph Error: cannot call getParent() with unreachable\n");
        exit(EXIT_FAILURE);
    }
    return G->F[u];
}

void addEdge(Graph G, int u, int v) {
    if (u > getOrder(G) || u < 1) {
        printf("Graph Error: cannot call addEdge() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v > getOrder(G) || v < 1) {
        printf("Graph Error: cannot call addEdge() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: cannot call addArc() on NULL reference \n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: cannot call addArc() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: cannot call addArc() with unreachable vertex\n");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    List A = G->adj[u];
    moveFront(A);

    while (n == 0 && index(A) != -1) {
        if (get(A) > v) {
            insertBefore(A, v);
            n = 1;
        } else {
            moveNext(A);
        }
    }
    if (0 > index(A)) {
        append(A, v);
    }
    G->size++;

}
     
     void Visit(Graph G, List S, int u, int *t) {
    if (G == NULL) {
        printf("Graph Error: cannot call Visit() on null graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        printf("Graph Error: cannot call Visit() on null list reference\n");
        exit(EXIT_FAILURE);
    }

    int k;
    List A = G->adj[u];
    G->D[u] = ++*t;
    G->C[u] = 1;

    for (moveFront(A); index(A) != UNDEF; moveNext(A)) {
        k = get(A);

        if (G->C[k] == 0) {
            G->P[k] = u;
            Visit(G, S, k, t);
        }
    }


    G->F[u] = ++*t;
    G->C[u] = 2;
    prepend(S, u);
}

void DFS(Graph G, List S) {
    if (G == NULL) {
        printf("Graph Error: cannot call DFS() on null graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        printf("Graph Error: cannot call DFS() on null list reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(S) != getOrder(G)) {
        printf("Graph Error: calling DFS() on different length of time and size of Graph is not the same\n");
        exit(EXIT_FAILURE);
    }

    int time, n, m, k;
    time = 0;
    n = getOrder(G);

    k = 1;
    while (k <= n) {
     
     G->C[k] = 0;
        G->P[k] = NIL;
        k++;
    }

    for (moveFront(S); index(S) != UNDEF; moveNext(S)) {
        m = get(S);

        if (G->C[m] == 0) {
            Visit(G, S, m, &time);
        }
    }

    k = 1;
    while (k <= n) {
        deleteBack(S);
        k++;
    }

}

Graph transpose(Graph G) {
    if (G == NULL) {
        printf("Graph Error: cannot call transpose() with a NULL Graph reference \n");
        exit(EXIT_FAILURE);
    }

    int k = 1;
    int n = getOrder(G);
    Graph Gt = newGraph(n);

    while (k <= n) {
        List A = G->adj[k];
        for (moveFront(A); index(A) != UNDEF; moveNext(A)) {
            addArc(Gt, get(A), k);
        }
        k++;
    }

    return Gt;
}


void printGraph(FILE *out, Graph G) {
    if (G == NULL) {
        printf("Graph Error: cannot call printGraph() with a  NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}

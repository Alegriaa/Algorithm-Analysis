// Brian Pereira Alegria
// brpereir
// Graph.h

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include<stdio.h>
#include "List.h"

#define INF -1
#define NIL 0
#define UNDEF -1

typedef struct GraphObj* Graph;


Graph newGraph(int n);

void freeGraph(Graph* pG);


int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */


void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */

void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */

void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

void Visit(Graph G, List S, int u, int *t);


Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out , Graph G);


#endif
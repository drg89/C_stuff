/*
graph.c

Set of vertices and edges implementation.

Implementations for helper functions for graph construction and manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "graph.h"
#include "utils.h"
#include "pq.h"
#include "list.h"
#define INITIALEDGES 32

struct edge;

/* Definition of a graph. */
struct graph {
  int numVertices;
  int numEdges;
  int allocedEdges;
  struct edge **edgeList;
};

/* Definition of an edge. */
struct edge {
  int start;
  int end;
  int cost;
};

struct graph *newGraph(int numVertices){
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  assert(g);
  /* Initialise edges. */
  g->numVertices = numVertices;
  g->numEdges = 0;
  g->allocedEdges = 0;
  g->edgeList = NULL;
  return g;
}

/* Adds an edge to the given graph. */
void addEdge(struct graph *g, int start, int end, int cost){
  assert(g);
  struct edge *newEdge = NULL;
  /* Check we have enough space for the new edge. */
  if((g->numEdges + 1) > g->allocedEdges){
    if(g->allocedEdges == 0){
      g->allocedEdges = INITIALEDGES;
    } else {
      (g->allocedEdges) *= 2;
    }
    g->edgeList = (struct edge **) realloc(g->edgeList,
      sizeof(struct edge *) * g->allocedEdges);
    assert(g->edgeList);
  }

  /* Create the edge */
  newEdge = (struct edge *) malloc(sizeof(struct edge));
  assert(newEdge);
  newEdge->start = start;
  newEdge->end = end;
  newEdge->cost = cost;

  /* Add the edge to the list of edges. */
  g->edgeList[g->numEdges] = newEdge;
  (g->numEdges)++;
}

/* Frees all memory used by graph. */
void freeGraph(struct graph *g){
  int i;
  for(i = 0; i < g->numEdges; i++){
    free((g->edgeList)[i]);
  }
  if(g->edgeList){
    free(g->edgeList);
  }
  free(g);
}

struct solution *graphSolve(struct graph *g, enum problemPart part,
  int antennaCost, int numHouses){
  struct solution *solution = (struct solution *)
    malloc(sizeof(struct solution));
  assert(solution);
  if(part == PART_A){
    /* IMPLEMENT 2A SOLUTION HERE */
    int totalCost = 0;
    int totalNodes = numHouses+1;
    int visited[totalNodes];
    int cmp[totalNodes];
    for(int i = 0; i < totalNodes;i++){
      visited[i] = 0;
      cmp[i]=1;
    }
    visited[0]=1;
    while( memcmp(visited, cmp, (size_t)totalNodes)!= 0 ){ //something here with memcmp maybe pointer issue
      //while there are still unvisited vertices
      int localMin = INT_MAX;
      int newVertex = -1;

      for(int i = 0; i < totalNodes; i++){
        if (visited[i]){
          //loop thru to find edges that connects visited to unvisited
          for(int j=0; j < g->numEdges; j++){
            struct edge *currEdge = g->edgeList[j];
            if (currEdge->start == i && !visited[currEdge->end]){
              //make sure this edge reaches an unvisited node
              if (currEdge->cost < localMin){
                localMin=currEdge->cost;
                newVertex = visited[currEdge->end];
              }
            }
          }
        }
      }
      totalCost += localMin;
      visited[newVertex] = 1;
      for(int i = 0; i < totalNodes; i++){
        printf("%d  ",visited[i]);
      }
      printf("\n");
    }
    solution->antennaTotal = numHouses * antennaCost;
    solution->cableTotal = totalCost;
    


  } else {
    /* IMPLEMENT 2C SOLUTION HERE */
    solution->mixedTotal = 0;
  }
  return solution;
}

#include "element.h"
#include "list.h"
#define MAX_VERTEX_COUNT 100

#ifndef GRAPH_H
#define GRAPH_H

  typedef struct matrixGraph {
    int vertexCount;
    Element* nodes[MAX_VERTEX_COUNT];
    int** adjacency;
  } MatrixGraph;
  typedef struct listGraph {
    int vertexCount;
    List* adjacency[MAX_VERTEX_COUNT];
  } ListGraph;

  MatrixGraph* createMatrixGraph(int);
  ListGraph* createListGraph(int);
  void addGraphNode(ListGraph*, MatrixGraph*, Element*);
  void addListGraphEdge(ListGraph*, Element*, Element*);
  void addMatrixGraphEdge(MatrixGraph*, Element*, Element*, int);
  int findMatrixGraphEdge(MatrixGraph*, Element*, Element*);
  int findListGraphEdge(ListGraph*, Element*, Element*);
  void freeGraphMemory(MatrixGraph*, ListGraph*);

#endif
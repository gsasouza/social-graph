#include "element.h"

#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VERTEX_COUNT 100

  typedef struct matrixGraph {
    int vertexCount;
    Element* nodes[MAX_VERTEX_COUNT];
    int** adjacency;
  } MatrixGraph;
  typedef struct listGraph ListGraph;

  MatrixGraph* createMatrixGraph(int);
  ListGraph* createListGraph(int);
  void addGraphNode(ListGraph*, MatrixGraph*, Element*);
  void addListGraphEdge(ListGraph*, Element*, Element*);
  void addMatrixGraphEdge(MatrixGraph*, Element*, Element*, int);
  void printElementNames(MatrixGraph*);
  int findMatrixGraphEdge(MatrixGraph*, Element*, Element*);
  int findListGraphEdge(ListGraph*, Element*, Element*);

#endif
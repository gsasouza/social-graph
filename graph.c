#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int** createMatrix(int size) {
  int** matrix = malloc(sizeof(int*) * size);
  for (int i = 0; i < size; ++i) {
    matrix[i] = malloc(sizeof(int) * size);
  }
  return matrix;
};

void createAdjacencyList(ListGraph* graph, int size) {
  int i;
  for (i = 0; i < MAX_VERTEX_COUNT; i++) {
    graph->adjacency[i] = createList(size);
  }
}

int findNodePositionByElement(MatrixGraph* graph, Element* element) {
  int i;
  for (i = 0; i < graph->vertexCount; i++) {
    Element* e = graph->nodes[i];
    if (compareElements(e, element)) return i;
  }
  return -1;
}

MatrixGraph* createMatrixGraph(int vertexCount) {
  MatrixGraph* graph = (MatrixGraph*) malloc(sizeof(MatrixGraph));
  graph->vertexCount = 0;
  graph->adjacency = createMatrix(vertexCount);

  for (int i = 0; i < vertexCount; i++) {
    for (int j = 0; j < vertexCount; j++) {
      graph->adjacency[i][j] = 0;
    }
  }
  return graph;
}

ListGraph* createListGraph(int vertexCount) {
  ListGraph* graph = (ListGraph*) malloc(sizeof(ListGraph));
  graph->vertexCount = vertexCount;
  createAdjacencyList(graph, vertexCount);
  return graph;
}

List* findElementInAdjacency(List* adjacency[MAX_VERTEX_COUNT], Element* element) {
  int i;
  for (i = 0; i < MAX_VERTEX_COUNT; i++) {
    List* list = adjacency[i];
    if (!list) continue;
    if (list->head) {
      if (compareElements(list->head->element, element)) return list;
    }
  }
  return NULL;
}

void addGraphNode(ListGraph* graph, MatrixGraph* matrixGraph, Element* element) {
  if (findNodePositionByElement(matrixGraph, element) != -1) return;
  matrixGraph->nodes[matrixGraph->vertexCount] = element;
  addToList(graph->adjacency[matrixGraph->vertexCount], createListNode(element));
  matrixGraph->vertexCount++;
}

void addListGraphEdge(ListGraph* graph, Element* source, Element* destination) {
  List* sourceList = findElementInAdjacency(graph->adjacency, source);
  List* destinationList = findElementInAdjacency(graph->adjacency, destination);
  if (!sourceList || !destinationList) return;
  // Não adiciona o memsmo elemento duas vezes
  if (!findElementInList(sourceList, destination)) addToList(sourceList, createListNode(destination));
  if (!findElementInList(destinationList, source)) addToList(destinationList, createListNode(source));
}

void addMatrixGraphEdge(MatrixGraph* graph, Element* source, Element* destination, int weight) {
  int sourcePosition = findNodePositionByElement(graph, source);
  int destinationPosition = findNodePositionByElement(graph, destination);
  if (
    graph->vertexCount== 0 ||
    sourcePosition == -1 ||
    destinationPosition == -1
  ) return;
  graph->adjacency[sourcePosition][destinationPosition] = weight;
  graph->adjacency[destinationPosition][sourcePosition] = weight;
}

int findMatrixGraphEdge(MatrixGraph* graph, Element* source, Element* destination) {
  int sourcePosition = findNodePositionByElement(graph, source);
  int destinationPosition = findNodePositionByElement(graph, destination);
  if (
    graph->vertexCount== 0 ||
    sourcePosition == -1 ||
    destinationPosition == -1
  ) return 0;
  return graph->adjacency[sourcePosition][destinationPosition];
}

int findListGraphEdge(ListGraph* graph, Element* source, Element* destination) {
  List* list = findElementInAdjacency(graph->adjacency, source);
  if (findElementInList(list, destination)) return 1;
  return 0;
}

void freeGraphMemory(MatrixGraph* matrixGraph, ListGraph* listGraph) {
  ListNode *aux;
  int i;
  for (i=0; i < listGraph->vertexCount; i++) {
    while (listGraph->adjacency[i]->head != NULL) {
      aux = listGraph->adjacency[i]->head;
      listGraph->adjacency[i]->head = listGraph->adjacency[i]->head->next;
      free(aux);
    }
  }
  free(listGraph);
  for (i=0; i < matrixGraph->vertexCount; i++) {
    free(matrixGraph->nodes[i]);
  }
  free(matrixGraph->adjacency);
  free(matrixGraph);
}

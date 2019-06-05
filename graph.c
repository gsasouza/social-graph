#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct element {
  char name[100];
  int age;
  char city[100];
  char favoriteMovie[100];
  char team[100];
  char favoriteColor[100];
};

Element* nameMap[MAX_VERTEX_COUNT];
int nameMapCount;

typedef struct listNode {
  Element* element;
  struct listNode* next;
} ListNode;

typedef struct list {
  ListNode* head;
  ListNode* tail;
} List;

struct matrixGraph {
  int vertexCount;
  int** adjacency;
};

struct listGraph {
  int vertexCount;
  List** adjacency;
};

int** createMatrix(int size) {
  int** matrix = malloc(sizeof(int*) * size);
  for (int i = 0; i < size; ++i) {
    matrix[i] = malloc(sizeof(int) * size);
  }
  return matrix;
};

List* createList(int size) {
  int i;
  List* l = (List*) malloc(sizeof(List) * size);
  for (i = 0; i < size; i++) {
    l[i].head = NULL;
    l[i].tail = NULL;
  }
  return l;
}

List** createAdjacencyList(int size) {
  int i;
  List** adjacency = (List**) malloc(sizeof(List) * MAX_VERTEX_COUNT);
  for (i = 0; i < MAX_VERTEX_COUNT; i++) {
    adjacency[i] = createList(size);
  }
  return adjacency;
}

int compareElements(Element* source, Element* match) {
  return (
    !strcmp(source->name, match->name) &&
    !strcmp(source->city, match->city) &&
    !strcmp(source->favoriteMovie, match->favoriteMovie) &&
    !strcmp(source->favoriteColor, match->favoriteColor) &&
    !strcmp(source->team, match->team) &&
    source->age == match->age
  );
}

int findEdgePositionByElement (Element* element) {
  int i;
  for (i = 0; i < MAX_VERTEX_COUNT; i++) {
    Element* e = nameMap[i];
    if (compareElements(e, element)) return i;
  }
  return -1;
}

MatrixGraph* createMatrixGraph(int vertexCount) {
  MatrixGraph* graph = (MatrixGraph*) malloc(sizeof(MatrixGraph));
  graph->vertexCount= vertexCount;
  graph->adjacency = createMatrix(vertexCount);

  for (int i = 0; i < vertexCount; i++) {
    for (int j = 0; j < vertexCount; j++) {
      graph->adjacency[i][j] = 0;
    }
  }
  return graph;
}

Element* createElement(
  char name[100],
  int age,
  char city[100],
  char favoriteMovie[100],
  char team[100],
  char favoriteColor[100]
){
  Element* element = (Element*) malloc(sizeof(Element));
  strcpy(element->name, name);
  element->age = age;
  strcpy(element->city, city);
  strcpy(element->favoriteMovie, favoriteMovie);
  strcpy(element->team, team);
  strcpy(element->favoriteColor, favoriteColor);
  return element;
}


ListGraph* createListGraph(int vertexCount) {
  ListGraph* graph = (ListGraph*) malloc(sizeof(ListGraph));
  graph->vertexCount= vertexCount;
  graph->adjacency = createAdjacencyList(vertexCount);
  return graph;
}

ListNode* createListNode(Element* element) {
  ListNode* listNode = (ListNode*) malloc(sizeof(ListNode));
  listNode->element = element;
  listNode->next = NULL;
  return listNode;
}

void addToList(List* list, ListNode* listNode) {
  ListNode* current = list->head;
  while(current->next) current = current->next;
  current->next = listNode;
  list->tail = listNode;
}

List* findElementInAdjacency(List** adjacency, Element* element) {
  int i;
  for (i = 0; i <MAX_VERTEX_COUNT; i++) {
    List* list = adjacency[i];
    if (list->head) {
      if (compareElements(list->head->element, element)) return list;
    }
  }
  return NULL;
}

ListNode* findElementInList(List* list, Element* element) {
  ListNode* current = list->head;
  while(current->next) {
    if (compareElements(element, current->element)) return current;
    current = current->next;
  }
  return NULL;
}

void addListGraphNode(ListGraph* graph, Element* element) {
  if (findEdgePositionByElement(element) == -1) return;
  nameMap[nameMapCount] = element;
  addToList(graph->adjacency[nameMapCount], createListNode(element));
  nameMapCount++;
}

void addListGraphEdge(ListGraph* graph, Element* source, Element* destination) {
  List* sourceList = findElementInAdjacency(graph->adjacency, source);
  List* destinationList = findElementInAdjacency(graph->adjacency, destination);
  if (!sourceList || !destinationList) return;
  // Não adiciona o memsmo elemento duas vezes
  if (!findElementInList(sourceList, destination)) addToList(sourceList, createListNode(destination));
  if (!findElementInList(destinationList, source)) addToList(destinationList, createListNode(destination));
}

void addMatrixGraphEdge(MatrixGraph* graph, Element* source, Element* destination, int weight) {
  int sourcePosition = findEdgePositionByElement(source);
  int destinationPosition = findEdgePositionByElement(destination);
  if (
    graph->vertexCount== 0 ||
    sourcePosition == -1 ||
    destinationPosition == -1
  ) return;
  graph->adjacency[sourcePosition][destinationPosition] = weight;
  graph->adjacency[destinationPosition][sourcePosition] = weight;
}

void printElementNames() {
  int i;
  for (i = 0; i < nameMapCount; i++) {
    printf("%s \n", nameMap[i]->name);
  }
}

int findMatrixGraphEdge(MatrixGraph* graph, Element* source, Element* destination) {
  int sourcePosition = findEdgePositionByElement(source);
  int destinationPosition = findEdgePositionByElement(destination);
  if (
    graph->vertexCount== 0 ||
    sourcePosition == -1 ||
    destinationPosition == -1
  ) return 0;
  return graph->adjacency[sourcePosition][destinationPosition];
}
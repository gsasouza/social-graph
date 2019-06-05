#include <stdio.h>
#include "graph.h"

int main() {
  Element* element1 = createElement(
    "beltrano",
    19,
    "São Carlos",
    "vingadores",
    "palmeiras",
    "azul"
  );
  Element* element2 = createElement(
    "ciclano",
    21,
    "São Carlos",
    "prometheus",
    "são caetano",
    "branco"
  );
  MatrixGraph* matrixGraph = createMatrixGraph(10);
  ListGraph* listGraph = createListGraph(10);
  addMatrixGraphEdge(matrixGraph, element1, element2, 1);

  printf("Hello, World!\n");
  return 0;
}
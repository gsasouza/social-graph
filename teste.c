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
  Element* element3 = createElement(
      "grafano",
      32,
      "São Carlos",
      "prometheus",
      "são caetano",
      "branco"
  );
  MatrixGraph* matrixGraph = createMatrixGraph(10);
  ListGraph* listGraph = createListGraph(10);
  addListGraphNode(listGraph, matrixGraph, element1);
  addListGraphNode(listGraph, matrixGraph, element2);
  addListGraphNode(listGraph, matrixGraph, element3);
  addMatrixGraphEdge(matrixGraph, element1, element2, 7);
  addListGraphEdge(listGraph, element1, element2);
  printElementNames(matrixGraph);
  printf("%d \n", findMatrixGraphEdge(matrixGraph, element1, element2));
  printf("%d \n", findMatrixGraphEdge(matrixGraph, element1, element3));
  printf("%d \n", findListGraphEdge(listGraph, element1, element2));
  printf("%d \n", findListGraphEdge(listGraph, element1, element3));
  return 0;
}
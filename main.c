#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "element.h"

void createSimilarityMatrix(MatrixGraph* matrixGraph) {
  int i = 0, j = 0;
  for (i = 0; i < matrixGraph->vertexCount; i++) {
    for(j = 0; j < matrixGraph->vertexCount; j++) {
      Element* source = matrixGraph->nodes[i];
      Element* match = matrixGraph->nodes[j];
      // Cria a aresta com peso se os elementos não forem o mesmo >> Diagonal principal é sempre 0;
      if (!compareElements(source, match)) matrixGraph->adjacency[i][j] = getElementsSimilarity(source, match);
    }
  }
}

void createElements(MatrixGraph* matrixGraph, ListGraph* listGraph) {
  addGraphNode(listGraph, matrixGraph, createElement("beltrano", 19, "São Carlos", "vingadores", "palmeiras", "azul"));
  addGraphNode(listGraph, matrixGraph, createElement("ciclano", 21, "São Carlos", "prometheus", "são caetano", "branco"));
  addGraphNode(listGraph, matrixGraph, createElement("grafano", 32, "São Carlos", "prometheus", "são caetano", "branco"));
}

void printMatrix(MatrixGraph* matrixGraph) {
  int i = 0, j = 0;
  for (i = 0; i < matrixGraph->vertexCount; i++) {
    for (j = 0; j < matrixGraph->vertexCount; j++) printf("%d ", matrixGraph->adjacency[i][j]);
    printf("\n");
  }
}


void menu(MatrixGraph* matrixGraph, ListGraph* listGraph) {
  int option = 0, selectedUser = 0;

  while(option >= 0 && option < 7){
    printf("***OPCOES***\n");
    printf("1. Listar Usuários Cadastrados\n");
    printf("2. Imprimir Matriz de Relacionamentos\n");
    printf("Sua opcao: ");
    scanf("%d",&option);
    switch(option) {
      case 2: {
        printMatrix(matrixGraph);
      }
      default:
        continue;
    }
  }
}


int main() {
  MatrixGraph* matrixGraph = createMatrixGraph(20);
  ListGraph* listGraph = createListGraph(20);
  createElements(matrixGraph, listGraph);
  createSimilarityMatrix(matrixGraph);
  menu(matrixGraph, listGraph);
  return 0;
}
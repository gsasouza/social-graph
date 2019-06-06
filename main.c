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

void printUsers(MatrixGraph* graph) {
  int i;
  for (i = 0; i < graph->vertexCount; i++) {
    printf("%d - %s \n", i, graph->nodes[i]->name);
  }
}

void printUsersWithSimilarity(MatrixGraph* graph, int* selectedUser) {
  int i;
  for (i = 0; i < graph->vertexCount; i++) {
    if (i == *selectedUser) continue;
    printf("%d - %s (Afinidade: %d%%) \n", i, graph->nodes[i]->name, graph->adjacency[*selectedUser][i] * 100 / 6);
  }
}

void printSelectedElement(MatrixGraph* graph, int selectedUser) {
  Element* user = graph->nodes[selectedUser];
  printf("Usuário Selecionado: %d - %s \n", selectedUser, user->name);
}

void printSeparator() {
  printf("-----------------------------------\n");
}

void selectUser(MatrixGraph* matrixGraph, int* selectedUser) {
  while(1){
    printf("Escolha o usuário: ");
    scanf("%d", selectedUser);
    if ((*selectedUser) < 0 || (*selectedUser) > matrixGraph->vertexCount - 1) {
      printf("Usuário Inválido, digite novamente \n");
      continue;
    }
    return;
  }
}

void waitForUser() {
  printSeparator();
  printf("Digite qualquer teclar para continuar ...");
  getchar();
  getchar();
}

void printUserFriends(ListGraph* listGraph, int* selectedUser) {
  List* list = listGraph->adjacency[*selectedUser];
  ListNode* user = list->head;
  ListNode* friend = user->next;
  if (!friend) {
    printf("Esse usuário ainda não tem nenhum amigo :(\n");
    return;
  }
  while (friend) {
    printf(" - %s \n", friend->element->name);
    friend = friend->next;
  }
}

void manageInvite(ListGraph* listGraph, int* selectedUser, int* count) {
  int option = 0, j = 0;
  List* list = listGraph->adjacency[*selectedUser];
  ListNode* user = list->head;
  List* invites = user->element->invites;
  ListNode* invite = invites->head;
  while(1) {
    printf("Selecione o convite: ");
    scanf("%d", &option);
    if (option < 0 || option > (*count)) {
      printf("Opção Inválida. \n");
      continue;
    }
    break;
  }
  for(invite; invite->next != NULL; invite = invite->next){
    if (*count == j) break;
    j++;
  }
  addListGraphEdge(listGraph, user->element, invite->element);
  removeElementFromList(invites, invite->element);
}

void printUserInvites(ListGraph* listGraph, MatrixGraph* matrixGraph, int* selectedUser) {
  List* list = listGraph->adjacency[*selectedUser];
  ListNode* user = list->head;
  List* invites = user->element->invites;
  ListNode* invite = invites->head;
  int count = 0, option = 0;
  if (!invite) {
    printf("Esse usuário ainda não tem nenhum convite :(\n");
    return;
  }
  for(ListNode* i = invite; i != NULL; i = i->next){
    // @TODO display similarity
    printf("%d - %s \n", count, invite->element->name);
    count++;
  }
  printSeparator();
  printf("Deseja aceitar ou recusar alguma solicitação? (1. Sim / 2.Não) \n");
  scanf("%d", &option);
  if (option == 1) {
    manageInvite(listGraph, selectedUser, &count);
  }
}

void sendInvite(ListGraph* listGraph, MatrixGraph* matrixGraph, int* selectedUser) {
  int option = 0;
  while(1) {
    printSeparator();
    printUsersWithSimilarity(matrixGraph, selectedUser);
    printf("Selecione o usuário: ");
    scanf("%d", &option);
    if (option < 0 || option > matrixGraph->vertexCount - 1) {
      printf("Opção Inválida. \n");
    }
    else break;
  }
  addToList(
    listGraph->adjacency[option]->head->element->invites,
    createListNode(listGraph->adjacency[*selectedUser]->head->element)
  );
}

void menu(MatrixGraph* matrixGraph, ListGraph* listGraph) {
  int option = 0, selectedUser = 0;
  while(option >= 0 && option < 7){
    setbuf(stdout, 0);
    printSeparator();
    printSelectedElement(matrixGraph, selectedUser);
    printSeparator();
    printf("***OPCOES***\n");
    printf("1. Listar Usuários Cadastrados\n");
    printf("2. Trocar de Usuário\n");
    printf("3. Meus Amigos\n");
    printf("4. Meus Convites de Amizade\n");
    printf("5. Enviar Convite de Amizade\n");
    printf("6. Lista de Sugestões\n");
    printf("7. Buscar Amor Verdadeiro\n");
    printf("8. Amigos com pouca afinidade\n");
    printf("9. Sair\n");
    printf("Sua opcao: ");
    scanf("%d",&option);
    printSeparator();
    switch(option) {
      case 1: {
        printUsers(matrixGraph);
        waitForUser();
        break;
      }
      case 2: {
        selectUser(matrixGraph, &selectedUser);
        break;
      }
      case 3: {
        printUserFriends(listGraph, &selectedUser);
        waitForUser();
        break;
      }
      case 4: {
        printUserInvites(listGraph, matrixGraph, &selectedUser);
        waitForUser();
        break;
      }
      case 5: {
        sendInvite(listGraph, matrixGraph, &selectedUser);
//        waitForUser();
        break;
      }
      case 9: return;
      default:
        printf("Opção Inválida \n");
        continue;
    }

  }
}

//@TODO test invite/accept/refuse friend flow
int main() {
  MatrixGraph* matrixGraph = createMatrixGraph(20);
  ListGraph* listGraph = createListGraph(20);
  createElements(matrixGraph, listGraph);
  createSimilarityMatrix(matrixGraph);
  menu(matrixGraph, listGraph);
  return 0;
}
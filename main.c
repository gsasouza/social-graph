#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "element.h"
#include "mergesort.h"

void printSeparator() {
  printf("<------------------------------------------------------------------------>\n");
}

void printLogo() {
  printf("   _____            _       __   ______                 __  \n");
  printf("  / ___/____  _____(_)___ _/ /  / ____/________ _____  / /_ \n");
  printf("  \\__ \\/ __ \\/ ___/ / __ `/ /  / / __/ ___/ __ `/ __ \\/ __ \\\n");
  printf(" ___/ / /_/ / /__/ / /_/ / /  / /_/ / /  / /_/ / /_/ / / / /\n");
  printf("/____/\\____/\\___/_/\\__,_/_/   \\____/_/   \\__,_/ .___/_/ /_/ \n");
  printf("                                             /_/            \n");
}

void removeBreakLine(char* str) {
  size_t len = strlen(str);
  if(str[len-1] == '\n' )
    str[len-1] = 0;
}

size_t removeProperty(char *str, size_t n) {
  size_t len = strlen(str);
  if (n > len)
    n = len;
  memmove(str, str + n, len - n + 1);
  removeBreakLine(str);
  return(len - n);
}

void createUsers (MatrixGraph* matrixGraph, ListGraph* listGraph) {
  FILE* file = fopen("users.in", "r"); // read mode;
  char* line[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  size_t propertySizes[9] = {17, 7, 8, 8, 24, 15, 18, 16};
  size_t len = 0;
  ssize_t read;
  size_t i;
  int count = 0;
  if (file == NULL) exit(EXIT_FAILURE);

  while ((getline(&line[count], &len, file)) != -1){
    if(!strcmp(line[count], "\n")) {
      count = -1;
      for (i = 0; i < 8; i ++) {
        removeProperty(line[i], propertySizes[i]);
      }
      addGraphNode(
        listGraph,
        matrixGraph,
        createElement(line[0], (int) line[1], line[2], line[3], line[4], line[5], line[6], line[7])
      );
    }
    count++;
  }
  for (i = 0; i < 9; i ++) {
    free(line[i]);
  }
  fclose(file);
}

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

void printMatrix(MatrixGraph* matrixGraph) {
  int i = 0, j = 0;
  for (i = 0; i < matrixGraph->vertexCount; i++) {
    for (j = 0; j < matrixGraph->vertexCount; j++) printf("%d ", matrixGraph->adjacency[i][j]);
    printf("\n");
  }
}

void waitForUser() {
  printSeparator();
  printf("Digite qualquer teclar para continuar ...");
  getchar();
  getchar();
}

void printUsersOrderedByAffinity(ListGraph* listGraph, MatrixGraph* matrixGraph, int* selectedUser){
  int* row = matrixGraph->adjacency[(*selectedUser)];
  int i;
  MergeSortElement array[matrixGraph->vertexCount];
  for(i = 0; i < matrixGraph->vertexCount; i++){
    array[i] = *createMergeSortElement(matrixGraph->nodes[i], row[i]);
  }
  mergesort(array, matrixGraph->vertexCount);
  for(i = 0; i < matrixGraph->vertexCount; i++){
    if (i == *selectedUser) continue;
    printf("%d -%s (Afinidade: %d%%) \n", i, array[i].element->name, array[i].affinity * 100 / 6);
  }
}

void printUsers(MatrixGraph* graph) {
  int i;
  for (i = 0; i < graph->vertexCount; i++) {
    printf("%d - %s", i, graph->nodes[i]->name);
  }
}

void printUsersWithSimilarity(MatrixGraph* graph, int* selectedUser) {
  int i;
  for (i = 0; i < graph->vertexCount; i++) {
    if (i == *selectedUser) continue;
    printf("%d -%s (Afinidade: %d%%) \n", i, graph->nodes[i]->name, graph->adjacency[*selectedUser][i] * 100 / 6);
  }
}

void printSelectedElement(MatrixGraph* graph, int selectedUser) {
  Element* user = graph->nodes[selectedUser];
  printf("Usuário Selecionado: %d - %s \n", selectedUser, user->name);
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
  // @TODO add refuse invite

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
  while(option >= 0 && option < 9){
    setbuf(stdout, 0);
    printSeparator();
    printLogo();
    printSeparator();
    printSelectedElement(matrixGraph, selectedUser);
    printSeparator();
    printf("***OPCOES***\n");
    printf("1. Meus Amigos\n");
    printf("2. Meus Convites de Amizade\n");
    printf("3. Enviar Convite de Amizade\n");
    printf("4. Lista de Sugestões\n");
    printf("5. Buscar Amor Verdadeiro\n");
    printf("6. Amigos com Pouca afinidade\n");
    printf("7. Listar Usuários Cadastrados\n");
    printf("8. Trocar de Usuário\n");
    printf("9. Sair\n");
    printf("Sua opcao: ");
    scanf("%d",&option);
    printSeparator();
    switch(option) {
      case 1: {
        printUserFriends(listGraph, &selectedUser);
        waitForUser();
        break;
      }
      case 2: {
        printUserInvites(listGraph, matrixGraph, &selectedUser);
        waitForUser();
        break;
      }
      case 3: {
        sendInvite(listGraph, matrixGraph, &selectedUser);
        break;
      }
      case 4: {
        printUsersOrderedByAffinity(listGraph, matrixGraph, &selectedUser);
        break;
      }
      case 7: {
        printUsers(matrixGraph);
        waitForUser();
        break;
      }
      case 8: {
        selectUser(matrixGraph, &selectedUser);
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
  createUsers(matrixGraph, listGraph);
  createSimilarityMatrix(matrixGraph);
//  printMatrix(matrixGraph);
  menu(matrixGraph, listGraph);
  freeGraphMemory(matrixGraph, listGraph);
  return 0;
}
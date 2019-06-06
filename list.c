#include "list.h"
#include <stdlib.h>

List* createList(int size) {
  List* l = (List*) malloc(sizeof(List) * size);
  l->head = NULL;
  l->tail = NULL;
  return l;
}

void addToList(List* list, ListNode* listNode) {
  ListNode* current = list->head;
  if (!current) {
    list->head = listNode;
    list->tail = listNode;
    return;
  }
  while(current->next) current = current->next;
  current->next = listNode;
  list->tail = listNode;
}

ListNode* findElementInList(List* list, Element* element) {
  ListNode* current = list->head;
  while(current) {
    if (compareElements(element, current->element)) return current;
    current = current->next;
  }
  return NULL;
}

void removeElementFromList(List* list, Element* element) {
  ListNode* current = list->head;
  ListNode* aux = NULL;
  if (!current->next) {
    list->head = NULL;
  }
  while(current) {
    if (compareElements(element, current->element)) {
      aux = current;
      current = current->next;
      free(aux);
      return;
    }
    current = current->next;
  }
}

ListNode* createListNode(Element* element) {
  ListNode* listNode = (ListNode*) malloc(sizeof(ListNode));
  listNode->element = element;
  listNode->next = NULL;
  return listNode;
}

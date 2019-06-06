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
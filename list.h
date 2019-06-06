#include "element.h"
#ifndef LIST_H
#define LIST_H


  typedef struct listNode {
    Element* element;
    struct listNode* next;
  } ListNode;

  typedef struct list {
    ListNode* head;
    ListNode* tail;
  } List;

  List* createList(int);
  void addToList(List*, ListNode*);
  ListNode* findElementInList(List*, Element*);
  void removeElementFromList(List*, Element*);
  ListNode* createListNode(Element* element);
#endif

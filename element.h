#ifndef ELEMENT_H
#define ELEMENT_H
  typedef struct element {
    char name[100];
    int age;
    char city[100];
    char favoriteMovie[100];
    char team[100];
    char favoriteColor[100];
  } Element;
  int compareElements(Element*, Element*);
  Element* createElement(char[100], int, char[100], char[100], char[100], char[100]);
  int getElementsSimilarity(Element*, Element*);
#endif
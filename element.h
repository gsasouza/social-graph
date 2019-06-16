#ifndef ELEMENT_H
#define ELEMENT_H
  typedef struct list List;
  typedef struct element {
    char name[100];
    int age;
    char city[100];
    char state[100];
    char company[100];
    char favoriteColor[100];
    char favoriteMovie[100];
    char favoriteGame[100];
    char gender[11];
    List* invites;
  } Element;
  int compareElements(Element*, Element*);
  Element* createElement(char[100], int, char[100], char[100], char[100], char[100], char[100], char[100], char[11]);
  int getElementsSimilarity(Element*, Element*);
#endif
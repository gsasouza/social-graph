#include "element.h"
#include <string.h>
#include <stdlib.h>

int getElementsSimilarity(Element* source, Element* match) {
  int similarity = 0;
  if(!strcmp(source->name, match->name)) similarity++;
  if(!strcmp(source->city, match->city)) similarity++;
  if(!strcmp(source->favoriteMovie, match->favoriteMovie)) similarity++;
  if(!strcmp(source->favoriteColor, match->favoriteColor)) similarity++;
  if(!strcmp(source->team, match->team)) similarity++;
  if(source->age == match->age) similarity++;
  return similarity;
}

int compareElements(Element* source, Element* match) {
  return getElementsSimilarity(source, match) == 6;
}


Element* createElement(
    char name[100],
    int age,
    char city[100],
    char favoriteMovie[100],
    char team[100],
    char favoriteColor[100]
){
  Element* element = (Element*) malloc(sizeof(Element));
  strcpy(element->name, name);
  element->age = age;
  strcpy(element->city, city);
  strcpy(element->favoriteMovie, favoriteMovie);
  strcpy(element->team, team);
  strcpy(element->favoriteColor, favoriteColor);
  return element;
}

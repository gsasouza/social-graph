#include <string.h>
#include <stdlib.h>
#include "element.h"
#include "list.h"

int getElementsSimilarity(Element* source, Element* match) {
  int similarity = 0;
  if(!strcmp(source->name, match->name)) similarity++;
  if(!strcmp(source->city, match->city)) similarity++;
  if(!strcmp(source->state, match->state)) similarity++;
  if(!strcmp(source->company, match->company)) similarity++;
  if(!strcmp(source->favoriteMovie, match->favoriteMovie)) similarity++;
  if(!strcmp(source->favoriteColor, match->favoriteColor)) similarity++;
  if(!strcmp(source->favoriteGame, match->favoriteGame)) similarity++;
  if(source->age == match->age) similarity++;
  return similarity;
}

int compareElements(Element* source, Element* match) {
  return getElementsSimilarity(source, match) == 8;
}

Element* createElement(
  char name[100],
  int age,
  char city[100],
  char state[100],
  char company[100],
  char favoriteColor[100],
  char favoriteMovie[100],
  char favoriteGame[100],
  char gender[11]
){
  Element* element = (Element*) malloc(sizeof(Element));
  strcpy(element->name, name);
  element->age = age;
  strcpy(element->city, city);
  strcpy(element->state, state);
  strcpy(element->company, company);
  strcpy(element->favoriteMovie, favoriteMovie);
  strcpy(element->favoriteGame, favoriteGame);
  strcpy(element->favoriteColor, favoriteColor);
  strcpy(element->gender, gender);
  element->invites = (List*) malloc(sizeof(List));
  return element;
}

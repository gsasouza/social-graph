#include <stdlib.h>
#include "element.h"
#include "mergesort.h"

void sort(MergeSortElement *v, MergeSortElement *copy, int i, int f);
void merge(MergeSortElement *v, MergeSortElement *copy, int i, int m, int f);

MergeSortElement* createMergeSortElement(Element* element, int a) {
  MergeSortElement* mergeSortElement = malloc(sizeof(MergeSortElement));
  mergeSortElement->affinity = a;
  mergeSortElement->element = element;
  return mergeSortElement;
}

void sort(MergeSortElement *vector, MergeSortElement *copy, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(vector, copy, i, m);
  sort(vector, copy, m + 1, f);

  if (vector[m].affinity >= vector[m + 1].affinity) return;

  merge(vector, copy, i, m, f);
}

void decreasingMerge(MergeSortElement *vector, MergeSortElement *copy, int i, int m, int f) {
  int z, ivector = i, icopy = m + 1;

  for (z = i; z <= f; z++) copy[z] = vector[z];

  z = i;

  while (ivector <= m && icopy <= f) {
    if (copy[ivector].affinity < copy[icopy].affinity) vector[z++] = copy[ivector++];
    else vector[z++] = copy[icopy++];
  }

  while (ivector <= m) vector[z++] = copy[ivector++];

  while (icopy <= f) vector[z++] = copy[icopy++];
}

void decreasingSort(MergeSortElement *vector, MergeSortElement *copy, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(vector, copy, i, m);
  sort(vector, copy, m + 1, f);

  if (vector[m].affinity <= vector[m + 1].affinity) return;

  decreasingMerge(vector, copy, i, m, f);
}

void mergesort(MergeSortElement *vector, int n, int decreasing) {
  MergeSortElement* copy = malloc(sizeof(MergeSortElement) * n);
  if (decreasing) decreasingSort(vector, copy, 0, n - 1);
  else sort(vector, copy, 0, n - 1);
  free(copy);
}

void merge(MergeSortElement *vector, MergeSortElement *copy, int i, int m, int f) {
  int z, ivector = i, icopy = m + 1;

  for (z = i; z <= f; z++) copy[z] = vector[z];

  z = i;

  while (ivector <= m && icopy <= f) {
    if (copy[ivector].affinity > copy[icopy].affinity) vector[z++] = copy[ivector++];
    else vector[z++] = copy[icopy++];
  }

  while (ivector <= m) vector[z++] = copy[ivector++];

  while (icopy <= f) vector[z++] = copy[icopy++];
}
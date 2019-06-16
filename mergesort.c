#include <stdlib.h>
#include "element.h"
#include "mergesort.h"

void sort(MergeSortElement *v, MergeSortElement *c, int i, int f);
void merge(MergeSortElement *v, MergeSortElement *c, int i, int m, int f);

MergeSortElement* createMergeSortElement(Element* element, int a) {
  MergeSortElement* mergeSortElement = malloc(sizeof(MergeSortElement));
  mergeSortElement->affinity = a;
  mergeSortElement->element = element;
  return mergeSortElement;
}

void mergesort(MergeSortElement *v, int n) {
  MergeSortElement* copy = malloc(sizeof(MergeSortElement) * n);
  sort(v, copy, 0, n - 1);
  free(copy);
}

void sort(MergeSortElement *v, MergeSortElement *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  if (v[m].affinity >= v[m + 1].affinity) return;

  merge(v, c, i, m, f);
}

void merge(MergeSortElement *v, MergeSortElement *c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv].affinity > c[ic].affinity) v[z++] = c[iv++];
    else /* if (c[iv] > c[ic]) */ v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}
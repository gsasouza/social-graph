
#ifndef MERGESORT_H
#define MERGESORT_H
  typedef struct mergeSortElement {
    Element* element;
    int affinity;
  } MergeSortElement;

  void mergesort(MergeSortElement *v, int n);
  MergeSortElement* createMergeSortElement(Element* element, int affinity);
#endif

#define MAX_VERTEX_COUNT 100

typedef struct matrixGraph MatrixGraph;
typedef struct listGraph ListGraph;
typedef struct element Element;

MatrixGraph* createMatrixGraph(int);
ListGraph* createListGraph(int);
Element* createElement(char[100], int, char[100], char[100], char[100], char[100]);
void addListGraphNode(ListGraph*, Element*);
void addListGraphEdge(ListGraph*, Element*, Element*);
void addMatrixGraphEdge(MatrixGraph*, Element*, Element*, int);
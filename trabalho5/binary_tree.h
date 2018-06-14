#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef struct tree {
  int value;
  int height;
  struct tree* smaller;
  struct tree* bigger;
} Tree;


Tree *loadTreeFromFile(char[100]);

void showTree(Tree*);
void isFull(Tree*);
void searchValue(Tree*, int);
int getHeight(Tree*);
void removeValue(Tree*, int);
void printInOrder(Tree*);
void printPreOrder(Tree*);
void printPosOrder(Tree*);
void balanceTree(Tree*);
int amount_of_elements(Tree*);

#endif

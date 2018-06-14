#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef struct tree {
  int number;
  *struct tree left;
  *struct tree right;
} Tree;

Tree *loadTreeFromFile(char[100]);

void showTree(Tree*);
void isFull(Tree*);
void searchValue(Tree*, int);
void getHeight(Tree*);
void removeValue(Tree*, int);
void printInOrder(Tree*);
void printPreOrder(Tree*);
void printPosOrder(Tree*);
void balanceTree(Tree*);

#endif

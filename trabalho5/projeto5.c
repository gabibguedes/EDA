#include <stdio.h>
#include "binary_tree.h"

int main(){
  Tree * arvore;
  arvore = loadTreeFromFile("BSTs/bst6.txt");

  int tamanho = getHeight(arvore);
  printf("altura = %d\n", tamanho);
  // isFull(arvore);
  // searchValue(arvore,26);
  showTree(arvore);
  // printInOrder(arvore);
  // printf("\n");
  balanceTree(arvore);
  // printPreOrder(arvore);
  // printf("\n");
  // printPosOrder(arvore);
  // printf("\n");
  return 0;
}

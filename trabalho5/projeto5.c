#include <stdio.h>
#include "binary_tree.h"

int main(){
  Tree * arvore;
  arvore = loadTreeFromFile("BSTs/bst2.txt");

  // int tamanho = getHeight(arvore);
  // printf("altura = %d\n", tamanho);
  // isFull(arvore);
  // searchValue(arvore,26);
  showTree(arvore);
  return 0;
}

#include <stdio.h>
#include "binary_tree.h"

int main(){
  Tree * arvore;
  arvore = loadTreeFromFile("BSTs/bst1.txt");

  int tamanho = getHeight(arvore);
  printf("altura = %d\n", tamanho);
  isFull(arvore);
  searchValue(arvore,26);
  return 0;
}

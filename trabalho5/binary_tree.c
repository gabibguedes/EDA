#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "binary_tree.h"
#define NO_CHILD 9999999

Tree *loadTreeFromFile(char filename[100]){
  FILE *fp;
  Tree* root = (Tree*)(malloc(sizeof(Tree)));
  Tree* old_node, *new_branch;
  int number, place_not_found;
  char space;

  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("ERRO 404: Arquivo não encontrado\n");
  }

  fscanf(fp, "%d%c", &root->value, &space);
  root->smaller = NULL;
  root->bigger = NULL;
  root->height = 1;
  printf("inicio = %d\n", root->value);

  while(!feof(fp)){
    new_branch = (Tree*)(malloc(sizeof(Tree)));
    fscanf(fp, "%d%c", &new_branch->value, &space);
    new_branch->smaller = NULL;
    new_branch->bigger = NULL;

    old_node = root;
    printf("**************************************\n");
    printf("numero: %d\n", new_branch->value);

    int place_not_found = 1;

    while(place_not_found){
      if(new_branch->value > old_node->value){
        if(old_node->bigger == NULL){
          old_node->bigger = new_branch;
          place_not_found = 0;
          new_branch->height = old_node->height + 1;
          printf("Valor anterior = %d\n",old_node->value);
          printf("é maior\n");
          printf("%d\n",new_branch->height );
          printf("**************************************\n");
        }else{
          old_node = old_node->bigger;
        }
      }else{
        if(old_node->smaller == NULL){
          old_node->smaller = new_branch;
          place_not_found = 0;
          new_branch->height = old_node->height + 1;
          printf("Valor anterior = %d\n",old_node->value);
          printf("é menor\n");
          printf("%d\n",new_branch->height );
          printf("**************************************\n");
        }else{
          old_node = old_node->smaller;
        }
      }
    }
  }
  return root;
}

void showTree(Tree* root){
  // printf("%d ", root->value );
  // if (root->smaller != NULL) {
  //   showTree(root->smaller, root->height);
  // }
  // if (root->bigger != NULL) {
  //   showTree(root->bigger, root->height);
  // }
  // printf("\n");
  int spaces, spacesBetween, spaceAux;
  int **treeMatrix = (int**)(calloc(100, sizeof(int*)));
  for (int i = 0; i < 100; i++) {
    treeMatrix[i] = (int*)(calloc(getHeight(root),sizeof(int)));
  }

  putTreeInMatrix(root, treeMatrix);

  spaces = 8 * getHeight(root);
  spacesBetween = spaces;

  for (int line = 0; line < getHeight(root); line++) {
    for (int i = 0; i < spaces; i++) {
      printf(" ");
    }
    spaceAux = spaces;
    spaces = spaces/2 - 1;
    for (int column = 1; column < treeMatrix[line][0] + 1; column++) {
      if (treeMatrix[line][column] == NO_CHILD) {
        printf("  ");
      }else{
        printf("%02d ", treeMatrix[line][column]);
      }
      for (int i = 0; i < spacesBetween; i++) {
        printf(" ");
      }
    }
    spacesBetween = spaceAux - 2;
    printf("\n\n");
  }

}

void putTreeInMatrix(Tree* element, int**treeMatrix){
  int line, column, nextLine, nextColumn, amount_of_NC;
  line = element->height - 1;
  column = treeMatrix[line][0] + 1;

  treeMatrix[line][column] = element->value;
  treeMatrix[line][0]++;

  if (element->smaller != NULL) {
    putTreeInMatrix(element->smaller, treeMatrix);
  }else{
    nextLine = line + 1;
    for (int l = nextLine; l < getHeight(element); l++) {
      //IMPLEMENTAR A ARVORE DE NOCHILDS
    }
    // nextColumn = treeMatrix[nextLine][0] + 1;
    // treeMatrix[nextLine][nextColumn] = NO_CHILD;
    // treeMatrix[nextLine][0]++;
  }
  if (element->bigger != NULL) {
    putTreeInMatrix(element->bigger, treeMatrix);
  }else{
    nextLine = line + 1;
    for (int l = nextLine; l < getHeight(element); l++) {
      //IMPLEMENTAR A ARVORE DE NOCHILDS
    }
    // nextColumn = treeMatrix[nextLine][0] + 1;
    // treeMatrix[nextLine][nextColumn] = NO_CHILD;
    // treeMatrix[nextLine][0]++;
  }
}


  //     X   f: print x
  //   / \      print /\
  //  Y   Z     f(y) e f(z)
  // / \   \
  // E  H   p
  //   / \
  //  t   j
  // /
  //D

void isFull(Tree* root){
  int number_of_elements, height;
  height = getHeight(root);
  number_of_elements = pow(2, height) - 1;

  if (number_of_elements == amount_of_elements(root)) {
    printf("A árvore é cheia\n");
  }else{
    printf("A árvore não é cheia\n");
  }
}

int amount_of_elements(Tree* branch){
  if(branch == NULL){
    return 0;
  }else if(branch->smaller == NULL && (branch->bigger)){
    return 1;
  } else {
    return 1 + amount_of_elements(branch->smaller) + amount_of_elements(branch->bigger);
  }
}

void searchValue(Tree* root, int value){
  Tree *branch = root;
  Tree *daddy = NULL, *brother = NULL;
  int not_found = 1;

  while(not_found){
    if(value == branch->value){
      not_found = 0;
      printf("Elemento %d encontrado\n", value);
      printf("\tNível do nó: %d\n", branch->height);
      if (daddy == NULL) {
        printf("\tO elemento é a raiz\n");
      }else{
        printf("\tPai: %d\n", daddy->value);
      }
      if(daddy->smaller != NULL && (daddy->bigger != NULL)){
        printf("\tIrmão: %d\n", brother->value);
      }

    }else if (value > branch->value) {
      if (branch->bigger == NULL) {
        printf("Valor não pertence a árvore\n");
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->smaller;
        branch = branch->bigger;
      }
    }else{
      if(branch->smaller == NULL){
        printf("Valor não pertence a árvore\n");
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->bigger;
        branch = branch->smaller;
      }
    }
  }
}

int getHeight(Tree* root){
  if(root == NULL) {
    return 0;
  //folha :
} else if(root->smaller == NULL &&(root->bigger == NULL)){
    return root->height;

  //nó:
  }else{
    int height_s, height_b;
    height_s = getHeight(root->smaller);
    height_b = getHeight(root->bigger);

    if (height_b > height_s) {
      return height_b;
    }else{
      return height_s;
    }
  }
}

void removeValue(Tree* root, int value){
  Tree *branch = root;
  Tree *daddy = NULL, *brother = NULL;
  int not_found = 1;

  while(not_found){
    //Se for folha
    if(value == branch->value){
      not_found = 0;
      if(branch->bigger == NULL &&(branch->smaller == NULL)){
        if(branch == daddy->bigger){
          daddy->bigger = NULL;
        }else{
          daddy->smaller = NULL;
        }
        free(branch);

    //Se for nó com 2 filhos
    }else if(branch->smaller != NULL && (branch->bigger !=NULL)){
      Tree *heir = branch->bigger, *heir_father = branch;
      int heir_not_found = 1;
      while(heir_not_found){
        if(heir->smaller == NULL){
          heir_not_found = 0;

          //Pai recebe herdeiro
          if (daddy->smaller == branch) {
            daddy->smaller = heir;
          }else{
            daddy->bigger = heir;
          }

          //se herdeiro tiver 1 filho (bigger)
          if (heir->bigger != NULL) {
            if (heir_father->smaller == heir) {
              heir_father->smaller = heir->bigger;
            }else{
              heir_father->bigger = heir->bigger;
            }
          }
          free(branch);
        }else{
          heir_father = heir;
          heir = heir->smaller;
        }
      }

    //Se for nó e tiver 1 filho
    }else if (daddy != NULL){
      if (branch->value > daddy->value) {
        if (branch->smaller !=NULL) {
          daddy->bigger = branch->smaller;
        }else{
          daddy->bigger = branch->bigger;
        }
      }else{
        if (branch->smaller !=NULL) {
          daddy->smaller = branch->smaller;
        }else{
          daddy->smaller = branch->bigger;
        }
      }
    }

    }else if (value > branch->value) {
      if (branch->bigger == NULL) {
        printf("Valor não pertence a árvore\n");
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->smaller;
        branch = branch->bigger;
      }
    }else{
      if(branch->smaller == NULL){
        printf("Valor não pertence a árvore\n");
        not_found = 0;
      }else{
        daddy = branch;
        brother = branch->bigger;
        branch = branch->smaller;
      }
    }
  }
}

void printInOrder(Tree* root){

}

void printPreOrder(Tree* root){

}

void printPosOrder(Tree* root){

}

void balanceTree(Tree* root){

}

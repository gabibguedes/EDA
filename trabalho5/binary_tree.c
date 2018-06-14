#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "binary_tree.h"

Tree *loadTreeFromFile(char filename[100]){
  FILE *fp;
  Tree* root = (Tree*)(malloc(sizeof(Tree)));
  Tree* branch = (Tree*)(malloc(sizeof(Tree)));


  fopen(fp, filename, "r");
  if(fp == NULL){
    printf("ERRO 404: Arquivo não encotrado\n");
  }

  fscanf(fp, "%d%c")
}

void showTree(Tree* root){

}

void isFull(Tree* root){

}
void searchValue(Tree* root, int value){

}

void getHeight(Tree* root){

}

void removeValue(Tree* root, int value){

}

void printInOrder(Tree* root){

}

void printPreOrder(Tree* root){

}

void printPosOrder(Tree* root){

}

void balanceTree(Tree* root){

}

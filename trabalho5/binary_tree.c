#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binary_tree.h"
#define NO_CHILD 9999999

int maximum(int x, int y) {
  if(x > y){
    return x;
  }else{
    return y;
  }
}

int minimum(int x, int y) {
  if(x < y){
    return x;
  }else{
    return y;
  }
}

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

void showTree(Tree *root){
  for (int i = 0; i < getHeight(root); i++) {
    printNodesForLevel(root, i, getHeight(root) - 1);
  }
}

int getLevelUtil(Tree *root, int number, int level){
    if (root == NULL){
      return 0;
    }

    if (root->value == number){
      return level;
    }

    int downlevel = getLevelUtil(root->smaller, number, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(root->bigger, number, level+1);
    return downlevel;
}

int getLevel(Tree *root, int number){
    return getLevelUtil(root,number,1);
}

void printNodesForLevel(Tree *root, int level, int height) {
    int maxLengthPerEntry = 4;
    int width = (int) pow(2, height) * maxLengthPerEntry;
    int numElements = (int) pow(2, level);

    int widthForEachElement;
    if (getHeight(root) <= 5) {
      widthForEachElement = width / numElements;
    }else if (getHeight(root) <= 7){
      widthForEachElement = width / (2 *numElements);
    }else {
      widthForEachElement = width / (15.2 * numElements);
    }

    Tree **nodes = (Tree **) calloc(numElements, sizeof(Tree *));
    fillLevel(nodes, root, level, 0, 0);

    if (level > 0) {
        printSlahes(numElements, widthForEachElement, nodes);
    }

    for (int i = 0; i < numElements; i++) {
        if (nodes[i] != NULL) {
            printNode(widthForEachElement, nodes[i]->value);
        } else {
            printf("%*s", widthForEachElement, "");
        }
    }
    free(nodes);
    printf("\n");
}

void fillLevel(Tree *nodes[], Tree *node, int targetLevel, int level, int nr) {
    if (level == targetLevel) {
        nodes[nr] = node;
        return;
    }

    if (node->smaller != NULL) {
        fillLevel(nodes, node->smaller, targetLevel, level + 1, nr * 2);
    }
    if (node->bigger != NULL) {
        fillLevel(nodes, node->bigger, targetLevel, level + 1, nr * 2 + 1);
    }
}

void printNode(int widthForEachElement, int data) {
    char buf[20];
    sprintf(buf, "%02d", data);
    printCentered(widthForEachElement, buf);
}

//omit slahes if there is no data in that subtree
void printSlahes(int numElements, int widthForEachElement, Tree *const *nodes) {
    for (int i = 0; i < numElements; i += 2) {
        if (nodes[i] != NULL) {
            printf("%*s", widthForEachElement / 2, "");
            printCentered(widthForEachElement / 2, "/");
        } else {
            printf("%*s", widthForEachElement, "");
        }
        if (nodes[i + 1] != NULL) {
            printCentered(widthForEachElement / 2, "\\");
            printf("%*s", widthForEachElement / 2, "");
        } else {
            printf("%*s", widthForEachElement, "");
        }
    }
    printf("\n");
}

int maxDepth(Tree *node) {
    if (node == NULL) {
        return -1;
    } else {
        return maximum(maxDepth(node->smaller), maxDepth(node->bigger)) + 1;
    }
}

void printCentered(int width, char *str) {
    int emptySpace = (int) (width - strlen(str)) / 2;
    printf("%*s%s%*s", emptySpace, "", str, width - (int) strlen(str) - emptySpace, "");
}

// void showTree(Tree* root){
//   int spaces, spacesBetween, spaceAux;
//   int **treeMatrix = (int**)(calloc(100, sizeof(int*)));
//   for (int i = 0; i < 100; i++) {
//     treeMatrix[i] = (int*)(calloc(getHeight(root),sizeof(int)));
//   }
//
//   putTreeInMatrix(root, treeMatrix);
//
//   spaces = 8 * getHeight(root);
//   spacesBetween = spaces;
//
//   for (int line = 0; line < getHeight(root); line++) {
//     for (int i = 0; i < spaces; i++) {
//       printf(" ");
//     }
//     spaceAux = spaces;
//     spaces = spaces/2 - 1;
//     for (int column = 1; column < treeMatrix[line][0] + 1; column++) {
//       if (treeMatrix[line][column] == NO_CHILD) {
//         printf("  ");
//       }else{
//         printf("%02d ", treeMatrix[line][column]);
//       }
//       for (int i = 0; i < spacesBetween; i++) {
//         printf(" ");
//       }
//     }
//     spacesBetween = spaceAux - 2;
//     printf("\n\n");
//
//   }
//
//   for (int i = 0; i < getHeight(root); i++) {
//     for (int j = 0; j < 8; j++) {
//       if (treeMatrix[i][j] == NO_CHILD) {
//         printf("nc ");
//       }else{
//         printf("%02d ",treeMatrix[i][j]);
//
//       }
//     }
//     printf("\n");
//   }
// }
//
// void putTreeInMatrix(Tree* element, int**treeMatrix){
//   int line, column, nextLine, nextColumn, amount_of_NC, c;
//   line = element->height - 1;
//   column = treeMatrix[line][0] + 1;
//
//   treeMatrix[line][column] = element->value;
//   treeMatrix[line][0]++;
//
//   if (element->smaller != NULL) {
//     putTreeInMatrix(element->smaller, treeMatrix);
//   }else{
//     nextLine = line + 1;
//     amount_of_NC = 1;
//     for (int l = nextLine; l < getHeight(element); l++) {
//       //IMPLEMENTAR A ARVORE DE NOCHILDS
//       printf("\n\n%ds NCs\n", amount_of_NC);
//       for (int nc = 0; nc < amount_of_NC; nc++) {
//         c = treeMatrix[l][0] + 1;
//         printf("%dº nc\n", nc + 1);
//         printf("l = %d\n", l);
//         printf("c = %d\n\n", c);
//         treeMatrix[l][c] = NO_CHILD;
//         treeMatrix[l][0]++;
//         printf("elemento: %d\n\n",treeMatrix[l][c] );
//       }
//       amount_of_NC = amount_of_NC * 2;
//     }
//   }
//   if (element->bigger != NULL) {
//     putTreeInMatrix(element->bigger, treeMatrix);
//   }else{
//     nextLine = line + 1;
//     amount_of_NC = 1;
//     for (int l = nextLine; l < getHeight(element); l++) {
//       printf("\n\n%ds NCs\n", amount_of_NC);
//       //IMPLEMENTAR A ARVORE DE NOCHILDS
//       for (int nc = 0; nc < amount_of_NC; nc++) {
//         c = treeMatrix[l][0];
//         printf("%dº nc\n", nc + 1);
//         printf("l = %d\n", l);
//         printf("c = %d\n\n", c + 1);
//         treeMatrix[l][c + 1] = NO_CHILD;
//         treeMatrix[l][0]++;
//         printf("elemento: %d\n\n",treeMatrix[l][c] );
//       }
//       amount_of_NC = amount_of_NC * 2;
//     }
//   }
// }

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
  if(root == NULL){
    return 0;
  }else{
    return 1 + maximum(getHeight(root->bigger), getHeight(root->smaller));
  }

//   if(root == NULL) {
//     return 0;
//   //folha :
// } else if(root->smaller == NULL &&(root->bigger == NULL)){
//     return root->height;
//
//   //nó:
//   }else{
//     int height_s, height_b;
//     height_s = getHeight(root->smaller);
//     height_b = getHeight(root->bigger);
//
//     if (height_b > height_s) {
//       return height_b;
//     }else{
//       return height_s;
//     }
//   }
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
  if (root->smaller != NULL) {
    printInOrder(root->smaller);
  }
  printf("%d ", root->value);
  if (root->bigger != NULL) {
    printInOrder(root->bigger);
  }
}

void printPreOrder(Tree* root){
  printf("%d ", root->value);
  if (root->smaller != NULL) {
    printPreOrder(root->smaller);
  }
  if (root->bigger != NULL) {
    printPreOrder(root->bigger);
  }
}

void printPosOrder(Tree* root){
  if (root->smaller != NULL) {
    printPosOrder(root->smaller);
  }
  if (root->bigger != NULL) {
    printPosOrder(root->bigger);
  }
  printf("%d ", root->value);
}

void balanceTree(Tree* root){
  Tree *daddy, *grandpa, *kid;
  if (isBalanced(root)) {
    printf("A árvore já está balanceada\n");
  }else{
    root = setBackbone(root);

    while (!isBalanced(root)) {
      grandpa = root;
      daddy = root;
      kid = daddy->bigger;
      if (kid != NULL) {
        root = rotationLeft(NULL, daddy, kid, root);
      }

      grandpa = daddy;
      daddy = kid;
      kid = daddy->bigger;

      while ((daddy->bigger != NULL) && !isBalanced(root)) {
        grandpa = daddy;
        daddy = kid;
        kid = daddy->bigger;

        if (kid != NULL) {
          root = rotationLeft(grandpa, daddy, kid, root);
        }

        grandpa = daddy;
        daddy = kid;
        kid = daddy->bigger;
      }
    }
  }
  showTree(root);
}

Tree * setBackbone(Tree *root){
  Tree *grandpa, *daddy, *kid;

  while (root->smaller != NULL) {
    root = rotationRight(NULL, root, root->smaller);
  }

  grandpa = root;
  daddy = root->bigger;

  while (daddy->bigger != NULL) {
    grandpa = root;
    daddy = root->bigger;

    while ((daddy->smaller == NULL) && (daddy->bigger !=NULL)) {
      grandpa = grandpa->bigger;
      daddy = daddy->bigger;
    }

    while(daddy->smaller != NULL) {
      daddy = rotationRight(grandpa, daddy, daddy->smaller);
    }
  }
  showTree(root );
  return root;
}

Tree* rotationRight(Tree *grandpa, Tree *daddy, Tree *kid){

  if (grandpa != NULL) {
    grandpa->bigger = kid;
  }

  daddy->smaller = kid->bigger;
  kid->bigger = daddy;

  return kid;
}


Tree* rotationLeft(Tree *grandpa, Tree *daddy, Tree *kid, Tree *root){
  kid->smaller = daddy;
  daddy->bigger = NULL;

  if (grandpa != NULL) {
    if (grandpa->smaller == daddy) {
      grandpa->smaller = kid;
    }else{
      grandpa->bigger = kid;
    }
  }

  if (daddy == root) {
    root = kid;
  }
  return root;
}

int isBalanced(Tree *root){
    int left_h = 0;
    int right_h = 0;

    if(root == NULL){
      return 1;
    }
    if (root->smaller != NULL) {
      left_h = getHeight(root->smaller);
    }
    if (root->bigger != NULL) {
      right_h = getHeight(root->bigger);
    }

    int smaller_height = minimum(left_h,right_h);
    int bigger_height = maximum(left_h,right_h);
    int differrence = bigger_height - smaller_height;

    if((differrence <= 1 ) && isBalanced(root->smaller) && isBalanced(root->bigger)){
      //Arvore balanceada
      return 1;
    } else{
      //Arvore não balanceada
      return 0;
    }
}

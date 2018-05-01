#include <stdio.h>
#include <stdlib.h>
#include "ilbp.h"

void reading_elements(int **matrix, int lines, int columns){
  for (int l = 1; l < lines - 1; l++) {
    for (int c = 1; c < columns - 1; c++) {
      //Aloca espaço para matriz 3x3
      int **little_matrix;
      //Preenche matriz 3x3
      little_matrix = matrix_reduced(matrix, l, c);
      print(little_matrix, 3,3);
      //Libera o espaço de memória de cada vetor
      for (int i = 0; i < 3; i++) {
        free(little_matrix[i]);
      }
      //Libera o espaço da matriz
      free(little_matrix);
    }
  }
}

int** matrix_reduced(int ** big_matrix, int line, int column) {
  int i=0, j=0;
  int** little_matrix = (int**) calloc(3, sizeof(int*));
  for (int i = 0; i < 3; i++) {
    little_matrix[i] = (int*) calloc(3, sizeof(int));
  }

  little_matrix[0][0] = big_matrix[line - 1][column - 1];
  little_matrix[0][1] = big_matrix[line - 1][column];
  little_matrix[0][2] = big_matrix[line - 1][column + 1];

  little_matrix[1][0] = big_matrix[line][column - 1];
  little_matrix[1][1] = big_matrix[line][column];
  little_matrix[1][2] = big_matrix[line][column + 1];

  little_matrix[2][0] = big_matrix[line + 1][column - 1];
  little_matrix[2][1] = big_matrix[line + 1][column];
  little_matrix[2][2] = big_matrix[line + 1][column + 1];

  print(little_matrix, 3,3);
  return little_matrix;
}


void print(int ** matrix, int lines, int columns){
  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      printf("%d ", matrix[l][c]);
    }
    printf("\n");
  }
}

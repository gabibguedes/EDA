#include <stdio.h>
#include <stdlib.h>
#include "ilbp.h"
#include "bin_operations.h"

void ILBP(int **matrix, int lines, int columns, int *super_vector){
  int **little_matrix, **binary_matrix, *binary_vector, dec_value, small_value;
  for (int l = 1; l < lines - 1; l++) {
    for (int c = 1; c < columns - 1; c++) {
      //Preenche matriz 3x3
      little_matrix = matrix_reduced(matrix, l, c);
      binary_matrix = comparing_elements(little_matrix);
      binary_vector = matrix_to_vector(binary_matrix);
      dec_value = binToDec(binary_vector);
      small_value = shift_amount(dec_value);
      super_vector[small_value]++;
      //Libera o espaço de memória de cada vetor
      for (int i = 0; i < 3; i++) {
        free(little_matrix[i]);
        free(binary_matrix[i]);
      }
      //Libera o espaço da matriz
      free(little_matrix);
      free(binary_matrix);
      free(binary_vector);
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

double calc_average(int** matrix) {
  int sum = 0;
  double result = 0;
  for (int l = 0; l < 3; l++) {
    for (int c = 0; c < 3; c++) {
      sum += matrix[l][c];
    }
  }
result = sum/9.0;
return result;
}

int ** comparing_elements(int** matrix){
  double average;
  average = calc_average(matrix);

  int** binary_matrix = (int**) calloc(3, sizeof(int*));
  for (int i = 0; i < 3; i++) {
    binary_matrix[i] = (int*) calloc(3, sizeof(int));
  }

  for(int l=0; l<3; l++){
    for(int c=0; c<3; c++){
      if (matrix[l][c]>=average) {
        binary_matrix[l][c] = 1;
      }
    }
  }
  return binary_matrix;
}


int* matrix_to_vector(int ** matrix){
  int* vector = (int*) calloc(9, sizeof(int));
  int i=0;
  for(int l=0; l<3; l++){
    for(int c=0; c<3; c++){
      vector[i] = matrix[l][c];
      i++;
    }
  }
  return vector;
}

void print_vector(int * vector){
  for(int i=0; i<9; i++){
    printf("%d ", vector[i]);
  }
  printf("\n");
}

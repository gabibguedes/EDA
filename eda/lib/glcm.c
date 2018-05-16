#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glcm.h"

void GLCM(int **matrix, int lines, int columns, double* super_vector){
  double *properties;
  properties = north(matrix, lines, columns);
  add_to_vector(513, properties, super_vector);
  properties = south(matrix, lines, columns);
  add_to_vector(516, properties, super_vector);
  properties = west(matrix, lines, columns);
  add_to_vector(519, properties, super_vector);
  properties = east(matrix, lines, columns);
  add_to_vector(522, properties, super_vector);
  properties = northeast(matrix, lines, columns);
  add_to_vector(525, properties, super_vector);
  properties = northwest(matrix, lines, columns);
  add_to_vector(528, properties, super_vector);
  properties = southeast(matrix, lines, columns);
  add_to_vector(531, properties, super_vector);
  properties = south_west(matrix, lines, columns);
  add_to_vector(534, properties, super_vector);

}

void add_to_vector(int position, double* properties, double * super_vector){
  for (int i=0; i<3; i++){
    super_vector[position + i] = properties[i];
  }
  free(properties);
}

double* north(int **matrix, int lines, int columns){ // Norte
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** north_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    north_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 1; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      element = matrix[l][c];
      neighbor = matrix[l-1][c];
      north_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(north_matrix);
  properties[1] = calc_homogeneity(north_matrix);
  properties[2] = calc_contrast(north_matrix);

  for (int i = 0; i < 256; i++) {
    free(north_matrix[i]);
  }
  free(north_matrix);
  return properties;
}

double* south(int **matrix, int lines, int columns){ // Sul
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** south_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    south_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 0; l < lines-1; l++) {
    for (int c = 0; c < columns; c++) {
      element = matrix[l][c];
      neighbor = matrix[l+1][c];
      south_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(south_matrix);
  properties[1] = calc_homogeneity(south_matrix);
  properties[2] = calc_contrast(south_matrix);

  for (int i = 0; i < 256; i++) {
    free(south_matrix[i]);
  }
  free(south_matrix);
  return properties;
}

double* west(int **matrix, int lines, int columns){ // Oeste (esquerda)
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** west_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    west_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 0; l < lines; l++) {
    for (int c = 1; c < columns; c++) {
      element = matrix[l][c];
      neighbor = matrix[l][c - 1];
      west_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(west_matrix);
  properties[1] = calc_homogeneity(west_matrix);
  properties[2] = calc_contrast(west_matrix);

  for (int i = 0; i < 256; i++) {
    free(west_matrix[i]);
  }
  free(west_matrix);
  return properties;
}

double* east(int **matrix, int lines, int columns){ // Leste (direita)
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** east_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    east_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns - 1; c++) {
      element = matrix[l][c];
      neighbor = matrix[l][c+1];
      east_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(east_matrix);
  properties[1] = calc_homogeneity(east_matrix);
  properties[2] = calc_contrast(east_matrix);

  for (int i = 0; i < 256; i++) {
    free(east_matrix[i]);
  }
  free(east_matrix);
  return properties;
}

double* northeast(int **matrix, int lines, int columns){ // Nordeste = norte + leste
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** northeast_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    northeast_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 1; l < lines; l++) {
    for (int c = 0; c < columns-1; c++) {
      element = matrix[l][c];
      neighbor = matrix[l-1][c + 1];
      northeast_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(northeast_matrix);
  properties[1] = calc_homogeneity(northeast_matrix);
  properties[2] = calc_contrast(northeast_matrix);

  for (int i = 0; i < 256; i++) {
    free(northeast_matrix[i]);
  }
  free(northeast_matrix);
  return properties;
}

double* northwest(int **matrix, int lines, int columns){ // Noroeste = norte + oeste
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** northwest_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    northwest_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 1; l < lines; l++) {
    for (int c = 1; c < columns; c++) {
      element = matrix[l][c];
      neighbor = matrix[l-1][c - 1];
      northwest_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(northwest_matrix);
  properties[1] = calc_homogeneity(northwest_matrix);
  properties[2] = calc_contrast(northwest_matrix);

  for (int i = 0; i < 256; i++) {
    free(northwest_matrix[i]);
  }
  free(northwest_matrix);
  return properties;
}

double* southeast(int **matrix, int lines, int columns){ // Sudeste = sul + leste
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** southeast_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    southeast_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 1; l < lines-1; l++) {
    for (int c = 0; c < columns-1; c++) {
      element = matrix[l][c];
      neighbor = matrix[l+1][c+1];
      southeast_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(southeast_matrix);
  properties[1] = calc_homogeneity(southeast_matrix);
  properties[2] = calc_contrast(southeast_matrix);

  for (int i = 0; i < 256; i++) {
    free(southeast_matrix[i]);
  }
  free(southeast_matrix);
  return properties;
}

double* south_west(int **matrix, int lines, int columns){ // Sudoeste = sul + oeste
  int element, neighbor;
  double* properties = (double*) calloc(3, sizeof(double));

  int** south_west_matrix = (int**) calloc(256, sizeof(int*));
  for (int i = 0; i < 256; i++) {
    south_west_matrix[i] = (int*) calloc(256, sizeof(int));
  }
  for (int l = 0; l < lines-1; l++) {
    for (int c = 1; c < columns; c++) {
      element = matrix[l][c];
      neighbor = matrix[l+1][c-1];
      south_west_matrix[neighbor][element]++;
    }
  }
  properties[0] = calc_energy(south_west_matrix);
  properties[1] = calc_homogeneity(south_west_matrix);
  properties[2] = calc_contrast(south_west_matrix);

  for (int i = 0; i < 256; i++) {
    free(south_west_matrix[i]);
  }
  free(south_west_matrix);
  return properties;
}

double calc_energy(int **matrix){
  int i, j;
  double sum =0;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
      sum += pow(matrix[i][j],2.0);
    }
  }
  return sum;
}

double calc_homogeneity(int **matrix){
  int module, i, j;
  double sum = 0;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
      module = pow((i-j), 2.0);
      module = pow(module, 0.5);
      sum += matrix[i][j]/(1+module);
    }
  }
  return sum;
}

double calc_contrast(int **matrix){
    int result, i, j;
    double sum = 0;
    for(i = 0; i < 256; i++) {
        for(j = 0; j < 256; j++) {
          result = (pow((i - j), 2.0)* matrix[i][j]);
          sum += result;
        }
    }
    return sum;
}

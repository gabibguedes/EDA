#include <stdio.h>
#include "main_functions.h"

void vector_normalize(double *vector){
  double bigger = 0;

  for (int j = 0; j < 537; j++) {
    if (vector[j]>bigger)
      bigger = vector[j];
  }
  for (int k = 0; k < 537; k++) {
    vector[k] = (vector[k]/bigger);
  }
}

double vector_distance(double *vector, double *average_vector){
  double distance = 0;

  for (int i = 0; i < 537; i++) {
    distance += pow((vector[i]-average_vector[i]), 2.0);
  }
  distance = pow(distance, 0.5);
  return distance;
}

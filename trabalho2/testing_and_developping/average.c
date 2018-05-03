#include <stdio.h>
#include <stdlib.h>


double* vector_average(double** super_matrix){
  double*vector = (double*) calloc(537, sizeof(double));

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 537; j++) {
      vector[j]+= super_matrix[i][j];
    }
  }

  for (int i = 0; i < 537; i++) {
    vector[i]=vector[i]/100;
  }
  return vector;
}




int main(int argc, char const *argv[]) {

  //double vector[3][5]={{1, 2, 3, 4, 5},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5}};

  double**vector = (double **) calloc(3, sizeof(double*));
  for (int i = 0; i < 3; i++) {
    vector[i] = (double *) calloc(5, sizeof (double));
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      vector[i][j]= (j+1);
    }
  }
  vector_average(vector);

  for (int p = 0; p < 3; p++) {
    free(vector[p]);
  }

  return 0;
}

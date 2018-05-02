#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void vector_normalize(double *vector){
  double bigger = 0;

  for (int j = 0; j < 5; j++) {
    if (vector[j]>bigger)
      bigger = vector[j];
  }
  for (int k = 0; k < 5; k++) {
    printf("%lf\n", vector[k]/bigger);
  }
}



double vector_distance(double *vector, double *average_vector){

  double distance = 0;
  for (int i = 0; i < 5; i++) {
    distance += (vector[i] - average_vector[i]) * (vector[i] - average_vector[i]);
  }
  distance = sqrt(distance);


  return distance;

}


void vector_classification(double *vector, double *average_asphalt_vector, double *average_grass_vector){

  if (vector_distance(vector, average_asphalt_vector) < vector_distance(vector, average_grass_vector))
    printf("asfalto");
  else
    printf("grama");

}


int main(int argc, char const *argv[]) {

  double vector[5]={1, 2, 3, 4, 5};
  double average_grass_vector[5]={1, 2, 3, 4, 5};
  double average_asphalt_vector[5]={1, 3, 4, 5, 6};

  vector_normalize(vector);

  vector_classification(vector, average_asphalt_vector, average_grass_vector);



  return 0;
}

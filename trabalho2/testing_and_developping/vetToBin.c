#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *vetToBin (int *vet){

  int average = 0;
  int *vetBin = (int *) calloc(9, sizeof (int));

  for (int i = 0; i < 9; i++) {
    average += vet[i];
  }

  average = average/9;

  for (int i = 0; i < 9; i++) {
    if (vet[i] >= average )
      vetBin[i] = 1;

    else
      vetBin[i] = 0;
  }

  return vetBin;

}




int main() {
  int vetorBin[9];
  int vetor[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 9; i++) {
    vetorBin[i] = vetToBin(vetor)[i];
  }


  printf("%d", vetorBin[0]);
  printf("%d", vetorBin[1]);
  printf("%d", vetorBin[2]);
  printf("%d", vetorBin[3]);
  printf("%d", vetorBin[4]);
  printf("%d", vetorBin[5]);
  printf("%d", vetorBin[6]);
  printf("%d", vetorBin[7]);
  printf("%d", vetorBin[8]);



  return 0;
}

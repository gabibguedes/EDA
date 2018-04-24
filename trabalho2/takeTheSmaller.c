#include <stdio.h>

int binToDec (int *vet){
  int dec = 0;
  int powTwo[9] = {256, 128, 64, 32, 16, 8, 4, 2, 1};

  for (int i = 8; i >= 0; i--) {
    dec += powTwo[i] * vet[i];
  }
  return dec;
}

int takeTheSmaller(int *vet){
  int smaller = 513;
  int vetAux[9];
  for (int m = 0; m < 9; m++) {
    vetAux[i] = vet[8];
    for (int j = 1; j < 9; j++) {
      vetAux[j] = vet[j-1];
    }
    for (int k = 0; k < 9; k++) {
      vet[k]= vetAux[k];
    }
    if(binToDec(vetAux)< smaller){
      smaller= binToDec(vetAux);
    }
  }
  return smaller;
}

int main(int argc, char const *argv[]) {

  int vetor[9] = { 0, 1, 1, 1, 0, 1, 0, 1, 0};

  printf("%d", takeTheSmaller(vetor));

  return 0;
}

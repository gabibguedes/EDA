#include <stdio.h>

int binToDec (int *vet){
  int dec = 0;
  int powTwo[9] = {256, 128, 64, 32, 16, 8, 4, 2, 1};

  for (int i = 8; i >= 0; i--) {
    dec += powTwo[i] * vet[i];
  }

  return dec;
}


int main() {

  int vet[9] = { 0, 1, 1, 1, 0, 1, 0, 1, 0};
  int smaller = 513;
  int vetAux[9];
for (int m = 0; m < 9; m++) {
  for (int i = 0; i < 9; i++) {
    vetAux[i] = vet[8];
    for (int j = 1; j < 9; j++) {
      vetAux[j] = vet[j-1];
    }
  }
  printf("%d", vetAux[0]);
  printf("%d", vetAux[1]);
  printf("%d", vetAux[2]);
  printf("%d", vetAux[3]);
  printf("%d", vetAux[4]);
  printf("%d", vetAux[5]);
  printf("%d", vetAux[6]);
  printf("%d", vetAux[7]);
  printf("%d\n", vetAux[8]);

  for (int k = 0; k < 9; k++) {
    vet[k]= vetAux[k];
  }
  printf("%d\n", binToDec(vetAux));
  if(binToDec(vetAux)< smaller){
    smaller= binToDec(vetAux);
  }
}

printf("\n%d", smaller);

  return 0;
}

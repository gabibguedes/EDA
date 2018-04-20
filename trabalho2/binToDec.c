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

  int vetor[9] = { 0, 1, 0, 1, 0, 1, 0, 1, 0};

  printf("%d", binToDec(vetor));

  return 0;
}

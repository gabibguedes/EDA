#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(int argc, char const *argv[]) {

  int vetor[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int m = 0;
  int vetorbin[9];
  int vetorbinrot[9];
  int somabin = 0;
  int binfinal = 512;
  int potdois[9] = {256, 128, 64, 32, 16, 8, 4, 2, 1};

  for (int i = 0; i < 9; i++) {
    m += vetor [i];
  }

  m = m/9;

  for (int i = 0; i < 9; i++) {
    if (vetor[i] >= m )
      vetorbin[i] = 1;

    else
      vetorbin[i] = 0;
  }

for (int k = 0; k < 9; k++) {
  for (int i = 0; i < 9; i++) {

    vetorbinrot[i] = vetorbin[8];
    vetorbinrot[i+1] = vetorbin[i];
    vetorbinrot[i+2] = vetorbin[i+1];
    vetorbinrot[i+3] = vetorbin[i+2];
    vetorbinrot[i+4] = vetorbin[i+3];
    vetorbinrot[i+5] = vetorbin[i+4];
    vetorbinrot[i+6] = vetorbin[i+5];
    vetorbinrot[i+7] = vetorbin[i+6];
    vetorbinrot[i+8] = vetorbin[i+7];

    printf("%d", vetorbinrot[0]);
    printf("%d", vetorbinrot[1]);
    printf("%d", vetorbinrot[2]);
    printf("%d", vetorbinrot[3]);
    printf("%d", vetorbinrot[4]);
    printf("%d", vetorbinrot[5]);
    printf("%d", vetorbinrot[6]);
    printf("%d", vetorbinrot[7]);
    printf("%d\n", vetorbinrot[8]);

    for (int l = 8; l > 0; l--) {

      somabin += potdois[l] * vetorbin[l];

      if (somabin < binfinal) {
        binfinal = somabin;
      }

      somabin = 0;
    }

    for (int j = 0; i < 9; i++) {
      vetorbin[i] = vetorbinrot[i];
    }
  }
}





  return 0;
}

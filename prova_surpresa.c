#include <stdio.h>
int main (){
  int entrada[10];
  int soma, maiorSoma, inicio, fim;

  for (int i = 0; i < 10; i++) {
    scanf("%d", &entrada[i]);
  }

  int melhorVetor[10] = {0,0,0,0,0,0,0,0,0,0};
  maiorSoma = 0;

  for (int i = 0; i < 10; i++) {
    for (int j = i; j < 10; j++) {
      soma =0;

      for (int x = 0; x <= j; x++) {
        soma += entrada[x];
      }

      if (soma >= maiorSoma) {
        maiorSoma = soma;
        inicio = i;
        fim = j;
      }
    }
  }

  printf("\n\nVetor digitado:\n");

  for (int i = 0; i < 10; i++) {
    printf("%d ", entrada[i]);
  }

  printf("\n\nSubvetor com a maior soma:\n");

  for (int i = inicio; i <= fim; i++) {
    printf("%d ", entrada[i]);
  }

  printf("\n\nMaior soma = %d\n", maiorSoma);

  return 0;
}

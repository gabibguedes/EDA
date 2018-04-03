#include <stdio.h>

int fneuronio(float *, float *, float, int, int *);

int main() {
  int neuronio;
  float entrada[10],
        pesos[10],
        limiarT;

  printf("\nEscreva os valores de entrada:\n");

  for (int i = 0; i < 10; i++){
    printf("%do elemento: ", i+1);
    scanf("%f", &entrada[i]);
  }

  printf("\nEscreva os valores dos pesos:\n");

  for (int i = 0; i < 10; i++){
    printf("%do peso: ", i+1);
    scanf("%f", &pesos[i]);
  }

  printf("\nValor do limiar T: ");
  scanf("%f", &limiarT);

  fneuronio(entrada, pesos, limiarT, 10, &neuronio);

  if(neuronio){
    printf("\nNeurônio ativado!\n");
  }else{
    printf("\nNeurôno inibido!\n");
  }

  return 0;
}

int fneuronio (float * entrada, float * pesos, float limiarT, int tamanho, int * neuronio){
  double somap = 0;

  for(int i = 0; i < tamanho; i++){
    somap += entrada[i] * pesos[i];
  }

  if (limiarT < somap) {
     *neuronio = 1;
  }else{
    *neuronio = 0;
  }

}

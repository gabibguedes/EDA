#include <stdio.h>

int fneuronio(float *, float *, float *, int *);

int main() {
  int TAMANHO = 10, neuronio;
  float entrada[TAMANHO],
        pesos[TAMANHO],
        limiarT;

  printf("Escreva os valores de entrada:\n");

  for (int i = 0; i < TAMANHO; i++){
    printf("%do elemento: ", i+1);
    scanf("%f", &entrada[i]);
  }

  printf("Escreva os valores dos pesos:\n");

  for (int i = 0; i < TAMANHO; i++){
    printf("%do peso: ", i+1);
    scanf("%f", &pesos[i]);
  }

  printf("Valor do limiar T: ");
  scanf("%f", &limiarT);

  neuronio = fneuronio(entrada, pesos, &limiarT, &TAMANHO);

  if(neuronio){
    printf("\nNeurônio ativado!\n");
  }else{
    printf("\nNeurôno inibido!\n");
  }

  return 0;
}

int fneuronio (float * entrada, float * pesos, float * limiarT, int * tamanho){
  double somap = 0;

  for(int i = 0; i < *tamanho; i++){
    somap += entrada[i] * pesos[i];
  }

  if (*limiarT < somap) {
    return 1;
  }else{
    return 0;
  }

}

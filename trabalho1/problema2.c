/*
Estruturas de Dados 1

Professor: Mateus Mendelson
Turma: B

Alunos:
  Gabriela Barrozo Guedes - 16/0121612
  Felipe Campos de Almeida - 16/0119553
  Helena Bretas Goulart - 16/0124034
*/

#include <stdio.h>

void recebe_notas (float *, int, float *);
void conta_notas (float *, int, int *, int *);
int percent_aprov(int, int, float *, float *);

int main() {
  float notas[10], apr[10], pAprovados, pReprovados;
  int aprovados, reprovados, metadeAprovada;

  printf("Escreva as notas dos alunos:\n");

  for (int i = 0; i < 10; i++) {
    printf("%do aluno: ", i+1);
    scanf("%f", &notas[i]);
  }

  recebe_notas(notas, 10, apr);
  conta_notas(apr, 10, &aprovados, &reprovados);
  metadeAprovada = percent_aprov(aprovados, reprovados, &pAprovados, &pReprovados);

  printf("\nQuantidade de aprovados: %d\n", aprovados);
  printf("Quantidade de reprovados: %d\n", reprovados);

  printf("\nPercentual de aprovados: %.2f %%\n", pAprovados);
  printf("Percentual de reprovados: %.2f %%\n", pReprovados);

  if (metadeAprovada) {
    printf("\nMais da metade da turma foi aprovada!\n");
  }else{
    printf("\nHouve um alto índice de reprovação.\n");
  }

  return 0;
}

void recebe_notas (float *notas, int tamanho, float *apr){
  for (int i = 0; i < tamanho; i++){
    if (notas[i] >= 6.0) {
      apr[i] = 1;
    }else{
      apr[i] = 0;
    }
  }
}

void conta_notas (float *apr, int tamanho, int *aprovados, int *reprovados){
  *aprovados = 0;
  *reprovados = 0;

  for(int i=0; i < tamanho; i++){
    if (apr[i]==1) {
      *aprovados = *aprovados + 1;
    }else{
      *reprovados = *reprovados + 1;
    }
  }
}

int percent_aprov(int aprovados, int reprovados, float * pAprovados, float * pReprovados){
  int total = aprovados + reprovados;

  *pAprovados = ((aprovados * 1.0) / (total * 1.0)) * 100;
  *pReprovados = ((reprovados * 1.0) / (total * 1.0)) * 100;

  if (*pAprovados > 50) {
    return 1;
  }else{
    return 0;
  }


}

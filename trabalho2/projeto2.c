#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void chose_files(int *photos){
  int i, j, unique, random_number;

  srand(time(NULL));

  j=0;
  while (j<25) {
    unique = 1;
    //Escolhe um número aleatório de 1 a 50
    random_number = (rand() % 50) + 1;

    for (i = 0; i < j; i++) {
      //Compara o número escolhido com cada número já existente no vetor
      if (photos[i] == random_number) {
        unique = 0;
      }
    }
    //Se o número não for repetido ele é adicionado ao vetor
    if (unique){
      photos[j] = random_number;
      printf("%d ", photos[j]);
      j++;
    }
  }
  printf("\n" );

}


int main(){
  int photos[25];

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos);

  for (int i = 0; i < 25; i++) {
    //Para cada arquivo escolhido o programa exeuta...
  }

  return 0;
}

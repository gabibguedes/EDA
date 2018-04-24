#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int shift_amount(int value){
  int smaller = value;
  for(int i=0; i < 9; i++){
    value = ((value >> 1) | (value << 8)) & 511;
    if(value < smaller){
      smaller = value;
    }
  }
  return smaller;
}

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
      j++;
    }
  }
}
void ILBP(char file[100]){

}


int main(){
  int photos[25];
  char asphalt_file[] = "DataSet/asphalt/asphalt_";
  char grass_file[] = "DataSet/grass/grass_";
  char txt[] = ".txt\0";
  char file_name[100];

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos);

  for (int i = 0; i < 25; i++) {
    //Para cada arquivo escolhido o programa exeuta...

    //ASFALTO
    snprintf (file_name, 100, "%s%02d%s", asphalt_file, photos[i], txt );

    FILE *fp;
    fp = fopen(file_name, "r");

    //Contando colunas:
    int number, count_columns = 1;
    char semicolon;

    while (semicolon == ";") {
      fscanf(fp, "%d%c", &number, &semicolon);
      if(semicolon == ";"){
        count_columns ++;
      }
      printf("%c\n", semicolon);
    }
    printf("\n%d\n",count_columns );

    fclose(file_name);

    //ILBP(file_name);

  }

  return 0;
}

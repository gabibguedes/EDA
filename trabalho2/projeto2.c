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

void file_path(char *file_name_asphalt, char *file_name_grass, int number){
  char asphalt_file[] = "DataSet/asphalt/asphalt_";
  char grass_file[] = "DataSet/grass/grass_";
  char txt[] = ".txt\0";
  snprintf (file_name_asphalt, 100, "%s%02d%s", asphalt_file, number, txt );
  snprintf (file_name_grass, 100, "%s%02d%s", grass_file, number, txt );

}

int count_columns(char *file_name){
  int number, columns = 1, on_the_line = 1;
  char semicolon;

  FILE *fp;
  fp = fopen(file_name, "r");

  while (on_the_line) {
    fscanf(fp, "%d%c", &number, &semicolon);
    if(semicolon == ';'){
      columns ++;
    }else if(semicolon = '\n'){
      on_the_line = 0;
    }
  }

  fclose(fp);
  return columns;
}


int main(){
  int photos[25], columns, lines;
  char file_asphalt[100], file_grass[100];

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos);

  for (int i = 0; i < 25; i++) {
    //Para cada numero de arquivo escolhido o programa exeuta...

    //Monta os caminhos dos arquivos de grama e asfalto
    file_path(file_asphalt, file_grass, photos[i]);

    //ASFALTO
    columns = count_columns(file_asphalt);

    printf("File chosen: %s\n",file_asphalt );
    printf("number of columns: %d\n", columns);
    //ILBP(file_asphalt);

    //GRAMA
    columns = count_columns(file_grass);

    printf("File chosen: %s\n",file_grass );
    printf("number of columns: %d\n", columns);
    //ILBP(file_grass);

  }

  return 0;
}

#include "file_manipulation.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void file_path(char *file_name_asphalt, char *file_name_grass, int number){
  char asphalt_file[] = "DataSet/asphalt/asphalt_";
  char grass_file[] = "DataSet/grass/grass_";
  char txt[] = ".txt\0";
  snprintf (file_name_asphalt, 100, "%s%02d%s", asphalt_file, number, txt );
  snprintf (file_name_grass, 100, "%s%02d%s", grass_file, number, txt );

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

int count_lines(char *file_name){
  int number, lines = 0, on_file = 1;
  char line_break;

  FILE *fp;

  fp =fopen(file_name, "r");

  while(!feof(fp)){
    fscanf(fp, "%c", &line_break);
    if(line_break == '\n'){
      lines ++;
    }
  }
  return lines - 1;
}

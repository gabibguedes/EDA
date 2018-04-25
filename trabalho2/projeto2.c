#include <stdio.h>
#include "lib/file_manipulation.h"

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

void ILBP(char *file_name){

}

void GLCM(char *file_name){

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
    lines = count_lines(file_asphalt);

    printf("File chosen: %s\n",file_asphalt );
    printf("number of columns: %d\n", columns);
    printf("number of lines: %d\n", lines);

    //ILBP(file_asphalt);

    //GRAMA
    // columns = count_columns(file_grass);
    //lines = count_lines(file_grass);
    //
    //ILBP(file_grass);

  }

  return 0;
}

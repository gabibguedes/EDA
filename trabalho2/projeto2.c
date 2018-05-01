#include <stdio.h>
#include "lib/file_manipulation.h"
#include "lib/bin_operations.h"
#include "lib/ilbp.h"

int main(){
  int photos_test[25], photos_training[25], columns, lines;
  char file_asphalt[100], file_grass[100];
  int **file_matrix;

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos_test, photos_training);

  //for (int i = 0; i < 25; i++) {
    //Para cada numero de arquivo escolhido o programa exeuta...

    //Monta os caminhos dos arquivos de grama e asfalto
    file_path(file_asphalt, file_grass, photos_test[1]);

    //ASFALTO
    columns = count_columns(file_asphalt);
    lines = count_lines(file_asphalt);

    file_matrix = build_matrix(file_asphalt, lines, columns);
    reading_elements(file_matrix, lines, columns);
    printf("ok4\n");


//  }

  return 0;
}

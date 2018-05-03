#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "lib/file_manipulation.h"
#include "lib/bin_operations.h"
#include "lib/ilbp.h"
#include "lib/glcm.h"
#include "lib/main_functions.h"

//Função para atualizar a barra de loading
void print_loading(char *loading, int position){
  //Adiciona - a cada imagem nova calculada
  loading[position] = '-';
  mvprintw(1,0,"Carregando imagens, isso pode demorar um pouco");
  mvprintw(3,0,"[");
  //Atualiza a barra
  for (int l = 0; l < 100; l++) {
    mvprintw (3, l+1, "%c", loading[l]);
  }
  mvprintw(3,100,"]loading...\n");
  refresh ();
}

int main(){
  int photos_test[25], photos_training[25], columns, lines, load=0;
  char file_asphalt[100], file_grass[100], loading[100];
  int **file_matrix;

  //Inicializando vetor de loading zerado
  for (int i = 0; i < 100; i++) {
    loading[i] = ' ';
  }

  //Iniciando o super_vector para as 100 imagens;
  //Vetores de TREINAMENTO:
  //ASFALTO
  double**super_vector_asphalt_training = (double **) calloc(100, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_asphalt_training[i] = (double *) calloc(537, sizeof (double));
  }
  //GRAMA
  double**super_vector_grass_training = (double **) calloc(100, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_grass_training[i] = (double *) calloc(537, sizeof (double));
  }

  //Vetores de TESTE:
  //ASFALTO
  double**super_vector_asphalt_test = (double **) calloc(100, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_asphalt_test[i] = (double *) calloc(537, sizeof (double));
  }
  //GRAMA
  double**super_vector_grass_test = (double **) calloc(100, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_grass_test[i] = (double *) calloc(537, sizeof (double));
  }

  //Vetores para média de Grama e Asfalto
  double* average_grass = (double *) calloc(537, sizeof(double));
  double* average_asphalt = (double *) calloc(537, sizeof(double));

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos_test, photos_training);

  //Nova tela para loading
  //initscr ();
  //curs_set (0);

  //Começa a leitura dos arquivos e os calculos
  for (int i = 0; i < 25; i++) {
    //ARQUIVOS DE TESTE
    //Monta os caminhos dos arquivos de grama e asfalto
    file_path(file_asphalt, file_grass, photos_test[i]);

    //ASFALTO
    //calcula linhas e colunas:
    columns = count_columns(file_asphalt);
    lines = count_lines(file_asphalt);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_asphalt, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector_asphalt_test[i]);
    GLCM(file_matrix, lines, columns, super_vector_asphalt_test[i]);
    vector_normalize(super_vector_asphalt_test[i]);

    //print_loading(loading, load); //Atualiza a tela de loading
    load++;

    //GRAMA
    //calcula linhas e colunas:
    columns = count_columns(file_grass);
    lines = count_lines(file_grass);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_grass, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector_grass_test[i]);
    GLCM(file_matrix, lines, columns, super_vector_grass_test[i]);
    vector_normalize(super_vector_grass_test[i]);

    //print_loading(loading, load); //Atualiza a tela de loading
    load++;

    //ARQUIVOS DE TREINAMENTO
    //Monta os caminhos dos arquivos de grama e asfalto
    file_path(file_asphalt, file_grass, photos_training[i]);

    //ASFALTO
    //calcula linhas e colunas:
    columns = count_columns(file_asphalt);
    lines = count_lines(file_asphalt);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_asphalt, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector_asphalt_training[i]);
    GLCM(file_matrix, lines, columns, super_vector_asphalt_training[i]);
    vector_normalize(super_vector_asphalt_training[i]);

    //print_loading(loading, load);//Atualiza a tela de loading
    load++;

    //GRAMA
    //calcula linhas e colunas:
    columns = count_columns(file_grass);
    lines = count_lines(file_grass);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_grass, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector_grass_training[i]);
    GLCM(file_matrix, lines, columns, super_vector_grass_training[i]);
    vector_normalize(super_vector_grass_training[i]);
    //print_loading(loading, load);//Atualiza a tela de loading
    load++;
    printf("\nAsphalt test\n");
    for (int k = 0; k < 537; k++) {
      printf("%.1lf ", super_vector_asphalt_test[i][k]);
    }
    printf("\nGrass test\n");
    for (int k = 0; k < 537; k++) {
      printf("%.1lf ", super_vector_grass_test[i][k]);
    }
    printf("\nAsphalt training\n");
    for (int k = 0; k < 537; k++) {
      printf("%.1lf ", super_vector_asphalt_training[i][k]);
    }
    printf("\nGrass training\n");
    for (int k = 0; k < 537; k++) {
      printf("%.1lf ", super_vector_grass_training[i][k]);
    }
    printf("\n");
  }
  //Sai da tela de loading
  //endwin();

  return 0;
}

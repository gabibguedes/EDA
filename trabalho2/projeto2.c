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
  for (int l = 0; l < 50; l++) {
    mvprintw (3, l+1, "%c", loading[l]);
  }
  mvprintw(3,100,"]loading...\n");
  refresh ();
}

int main(){
  int photos_test[25], photos_training[25], columns, lines, load=0;
  char loading[50];

  //Inicializando vetor de loading zerado
  for (int i = 0; i < 50; i++) {
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
    //Para teste e treinamento é solucionado os vetores de 537 posições

    //ARQUIVOS DE TESTE
    ILBP_GLCM_vector(super_vector_asphalt_test[i], super_vector_grass_test[i], photos_test[i]);
    //print_loading(loading, load); //Atualiza a tela de loading
    load++;

    //ARQUIVOS DE TREINAMENTO
    ILBP_GLCM_vector(super_vector_asphalt_training[i], super_vector_grass_training[i], photos_training[i]);

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

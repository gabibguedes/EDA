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
  loading[position] = '#';
  mvprintw(1,0,"Carregando imagens, isso pode demorar um pouco");
  mvprintw(3,0,"[");
  //Atualiza a barra
  for (int l = 0; l < 50; l++) {
    mvprintw (3, l+1, "%c", loading[l]);
  }
  mvprintw(3,50,"]loading...\n");
  refresh ();
}

int main(){
  int photos_test[25], photos_training[25], columns, lines, load=0;
  char loading[50];
  double* average_grass, *average_asphalt;
  int hits = 0, hits_p, false_acceptance = 0, false_rejection = 0;

  //Inicializando vetor de loading zerado
  for (int i = 0; i < 50; i++) {
    loading[i] = ' ';
  }

  //Iniciando o super_vector para as 100 imagens;
  //Vetores de TREINAMENTO:
  //ASFALTO
  double**super_vector_asphalt_training = (double **) calloc(25, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_asphalt_training[i] = (double *) calloc(537, sizeof (double));
  }
  //GRAMA
  double**super_vector_grass_training = (double **) calloc(25, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_grass_training[i] = (double *) calloc(537, sizeof (double));
  }

  //Vetores de TESTE:
  //ASFALTO
  double**super_vector_asphalt_test = (double **) calloc(25, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_asphalt_test[i] = (double *) calloc(537, sizeof (double));
  }
  //GRAMA
  double**super_vector_grass_test = (double **) calloc(25, sizeof(double*));
  for (int i = 0; i < 25; i++) {
    super_vector_grass_test[i] = (double *) calloc(537, sizeof (double));
  }

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos_test, photos_training);

  //Nova tela para loading
  initscr ();
  curs_set (0);

  //Começa a leitura dos arquivos e os calculos
  for (int i = 0; i < 25; i++) {
    //Para teste e treinamento é solucionado os vetores de 537 posições

    //ARQUIVOS DE TESTE
    ILBP_GLCM_vector(super_vector_asphalt_test[i], super_vector_grass_test[i], photos_test[i]);
    print_loading(loading, load); //Atualiza a tela de loading
    load++;

    //ARQUIVOS DE TREINAMENTO
    ILBP_GLCM_vector(super_vector_asphalt_training[i], super_vector_grass_training[i], photos_training[i]);
    print_loading(loading, load);//Atualiza a tela de loading
    load++;
  }
  //Sai da tela de loading
  endwin();

  //Montando vetores de media
  average_asphalt = vector_average(super_vector_asphalt_training);
  average_grass = vector_average(super_vector_grass_training);

  //Liberando matrizes de treinamento
  for (int i = 0; i < 25; i++) {
    free(super_vector_asphalt_training[i]);
    free(super_vector_grass_training[i]);
  }
  free(super_vector_asphalt_training);
  free(super_vector_grass_training);

  for (int i = 0; i < 25; i++) {
    if(vector_classification(super_vector_asphalt_test[i], average_asphalt, average_grass)){
      hits++;
    }else{
      false_acceptance++;
    }
    if(!vector_classification(super_vector_grass_test[i], average_asphalt, average_grass)){
      hits++;
    }else{
      false_rejection++;
    }
  }
  hits_p = ((hits * 1.0)/50.0) * 100;
  false_acceptance = ((false_acceptance * 1.0)/25.0) * 100;
  false_rejection = ((false_rejection * 1.0)/25.0) * 100;

  printf("Porcentagem de Acertos: %d%% \n",hits_p );
  printf("Taxa de falsa aceitação: %d%% \n",false_acceptance );
  printf("Taxa de falsa rejeição: %d%% \n",false_rejection );

  return 0;
}

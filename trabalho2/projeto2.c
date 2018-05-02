#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/file_manipulation.h"
#include "lib/bin_operations.h"
#include "lib/ilbp.h"
#include "lib/glcm.h"

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
  int photos_test[25], photos_training[25], columns, lines, sv=0;
  char file_asphalt[100], file_grass[100], loading[100];
  int **file_matrix;

  //Iniciando o super_vector para as 100 imagens;
  int**super_vector = (int **) calloc(100, sizeof(int*));
  for (int i = 0; i < 100; i++) {
    super_vector[i] = (int *) calloc(537, sizeof (int));
    loading[i] = ' ';
  }

  //Escolhe os números dos arquivos a serem utilizados:
  chose_files(photos_test, photos_training);

  //Nova tela para loading
  initscr ();
  curs_set (0);

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
    ILBP(file_matrix, lines, columns, super_vector[sv]);
    GLCM(file_matrix, lines, columns, super_vector[sv]);

    print_loading(loading, sv); //Atualiza a tela de loading
    sv++; //Começa o proximo vetor de 537 posições

    //GRAMA
    //calcula linhas e colunas:
    columns = count_columns(file_grass);
    lines = count_lines(file_grass);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_asphalt, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector[sv]);
    GLCM(file_matrix, lines, columns, super_vector[sv]);

    print_loading(loading, sv); //Atualiza a tela de loading
    sv++; //Começa o proximo vetor de 537 posições

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
    ILBP(file_matrix, lines, columns, super_vector[sv]);
    GLCM(file_matrix, lines, columns, super_vector[sv]);

    print_loading(loading, sv);//Atualiza a tela de loading
    sv++;//Começa o proximo vetor de 537 posições

    //GRAMA
    //calcula linhas e colunas:
    columns = count_columns(file_grass);
    lines = count_lines(file_grass);

    //monta a matriz do arquivo
    file_matrix = build_matrix(file_asphalt, lines, columns);
    //Calcula o ILBP e GLCM
    ILBP(file_matrix, lines, columns, super_vector[sv]);
    GLCM(file_matrix, lines, columns, super_vector[sv]);

    print_loading(loading, sv);//Atualiza a tela de loading
    sv++;//Começa o proximo vetor de 537 posições
  }
  //Sai da tela de loading
  endwin();

  return 0;
}

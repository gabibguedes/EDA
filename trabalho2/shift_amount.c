#include <stdio.h>
int shift_amount(int valor){

  int menor = valor;
  for(int i=0; i < 9; i++){
    valor = ((valor >> 1) | (valor << 8)) & 511;
    printf("%d\n", valor);
    if(valor < menor){
      menor = valor;
    }
  }
  return menor;
}

int main(){
  int valor;
  printf("Escreva um numero: ");
  scanf("%d",&valor );
  printf("\n%d\n",shift_amount(valor));
  //int aux = 3;
  //valor = (aux << 2);
  //printf("%d\n", valor);
  return 0;
}


// 000110001 49
// 100011000 280
// 010001100 140
// 001000110 70
// 000100011 35
// 100010001 273
// 110001000 292
// 011000100 196
// 001100010 98
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bin_operations.h"

int binToDec (int *vet){
  int dec = 0;
  int powTwo[9] = {256, 128, 64, 32, 16, 8, 4, 2, 1};

  for (int i = 8; i >= 0; i--) {
    dec += powTwo[i] * vet[i];
  }

  return dec;
}

int *vetToBin (int *vet){

  int average = 0;
  int *vetBin = (int *) calloc(9, sizeof (int));

  for (int i = 0; i < 9; i++) {
    average += vet[i];
  }

  average = average/9;

  for (int i = 0; i < 9; i++) {
    if (vet[i] >= average )
      vetBin[i] = 1;

    else
      vetBin[i] = 0;
  }

  return vetBin;

}

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

#ifndef _GLCM_H_
#define _GLCM_H_

void GLCM(int **, int, int, int*);
void add_to_vector(int, int*, int *);
int* north(int **, int, int);
int* south(int **, int, int);
int* west(int **, int, int);
int* east(int **, int, int);
int* northeast(int **, int, int);
int* northwest(int **, int, int);
int* southeast(int **, int, int);
int* south_west(int **, int, int);
int calc_energy(int **);
int calc_homogeneity(int **);
int calc_contrast(int **);

#endif

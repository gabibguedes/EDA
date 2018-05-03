#ifndef _GLCM_H_
#define _GLCM_H_

void GLCM(int **, int, int, double*);
void add_to_vector(int, double*, double *);
double* north(int **, int, int);
double* south(int **, int, int);
double* west(int **, int, int);
double* east(int **, int, int);
double* northeast(int **, int, int);
double* northwest(int **, int, int);
double* southeast(int **, int, int);
double* south_west(int **, int, int);
double calc_energy(int **);
double calc_homogeneity(int **);
double calc_contrast(int **);

#endif

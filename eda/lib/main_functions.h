#ifndef _MAIN_FUNCTIONS_H_
#define _MAIN_FUNCTIONS_H_

void ILBP_GLCM_vector(double*, double*, int);
void vector_normalize(double *);
int vector_classification(double *, double *, double *);
double vector_distance(double *, double *);
double* vector_average(double**);

#endif

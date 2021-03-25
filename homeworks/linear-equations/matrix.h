#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>

void print_vector(gsl_vector* v);
void print_matrix(gsl_matrix* m);
void generate_vector(gsl_vector* v);
void generate_matrix(gsl_matrix* A);
double in_prod(gsl_vector* a, gsl_vector* b);
double norm(gsl_vector* a, gsl_vector* b);
void backsub(gsl_matrix* U, gsl_vector* c);
void GS_decomp(gsl_matrix* A, gsl_matrix* R);
void GS_solve(gsl_matrix* Q, gsl_matrix* R, gsl_vector* b, gsl_vector* x);
void GS_decomp2(gsl_matrix *A, gsl_matrix *R);
void GS_decomp3(gsl_matrix *A, gsl_matrix *R);
 

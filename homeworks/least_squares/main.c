#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>


double f0(double x) {
    return 1.;
}

double f1(double x){
    return x;
}

void least_squares(double (*f)(double), gsl_vector *x, gsl_vector *y, gsl_vector *y_err, gsl_vector *par, gsl_matrix *cov);

int main() {

    // Fitting function 
    double (*f[])(double) = {f0, f1};

    // Create vectors with data from a filestream
    int n = 9; // Number of points
    gsl_vector *x = gsl_vector_alloc(n);
    gsl_vector *y = gsl_vector_alloc(n);
    gsl_vector *dy = gsl_vector_alloc(n);

    FILE* x_data = fopen("x_data.txt", "r");
    FILE* y_data = fopen("y_data.txt", "r");
    gsl_vector_fscanf(x_data, x);
    gsl_vector_fscanf(y_data, y);

    // Error is dy = y/20
    gsl_vector_memcpy(dy, y);
    gsl_vector_scale(dy, 1.0/20);

    // Allocate memory for parameter vector and covariance matrix
    int m = 2; // number of parameters
    gsl_vector *par = gsl_vector_alloc(m);
    gsl_matrix *cov = gsl_matrix_alloc(m, m);

    // Do the least squares method
    least_squares(f, x, y, dy, par, cov);
    return 0;
}
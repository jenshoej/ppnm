#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

// Used for printing a matrix
void print_matrix(gsl_matrix* m) {
	for(int i = 0; i < m->size1; i++){
		for(int j = 0; j < m->size2; j++) {
			printf("%10.4f", gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
	printf("\n");
}

// Linear function
double F(int i, double x) {
    switch(i) {
        case 0: return 1.0;
        case 1: return x;
        default: return NAN;
    }
}


void least_squares(int m, double (*f)(int, double), gsl_vector *x, gsl_vector *y, gsl_vector *y_err, gsl_vector *par, gsl_vector *par_err, gsl_matrix *cov);

int main() {

    // Fitting function 

    // Create vectors with data from a filestream
    int n = 9; // Number of points
    gsl_vector *x = gsl_vector_alloc(n);
    gsl_vector *y = gsl_vector_alloc(n);
    gsl_vector *dy = gsl_vector_alloc(n);

    // Open data from files and scan them to a gsl vector
    FILE* x_data = fopen("x_data.txt", "r");
    FILE* y_data = fopen("y_data.txt", "r");
    FILE* y_error = fopen("y_error.txt", "r");
    gsl_vector_fscanf(x_data, x);
    gsl_vector_fscanf(y_data, y);
    gsl_vector_fscanf(y_error, dy);

    // Print data to a file for plotting
    FILE* data = fopen("data.txt", "w");
    for(int i = 0; i < n; i++){
        fprintf(data, "%10.4f %10.4f %10.4f\n", gsl_vector_get(x, i), gsl_vector_get(y, i), gsl_vector_get(dy, i));
    }

    // Make data linear by: ln(y) = ln(a) - λt, dy = dy/y
    gsl_vector_div(dy, y);
    for (int i = 0; i < y->size; ++i) {
        gsl_vector_set(y, i, log(gsl_vector_get(y, i)));
    }

    // Allocate memory for parameter vector and covariance matrix
    int m = 2;
    gsl_vector *par = gsl_vector_alloc(m);
    gsl_vector *par_err = gsl_vector_alloc(m);
    gsl_matrix *cov = gsl_matrix_alloc(m, m);

    // Do the least squares method
    least_squares(m, &F, x, y, dy, par, par_err, cov);

    // Find the half life as ln(2)/λ, where λ is the second parameter. The logarithmic error is dy/y
    double lambda = -gsl_vector_get(par, 1);
    double dlambda = gsl_vector_get(par_err, 1);
    double error = dlambda/lambda;

    double halflife = log(2)/lambda;
    double halflife_err = halflife*error;
    printf("Halflife of ThX is %10.4f +/- %10.4f days\n", halflife, halflife_err);

    // The radioactive decay is given by y = a*e^(-lambda*t)
    // Print datapoints to a file for plotting
    FILE* plotting_data = fopen("plotting_data.txt", "w");
    int N = 100;
    for(int i = 0; i < N; i++) {
        double a = exp(gsl_vector_get(par, 0)); // Remember a is ln(a) so take exp(ln(a)) to get a
        double ti = 16.0 / N * i;
        double yi = a*exp(-lambda*ti);
        double yi_lower = a*exp(-(lambda-error)*ti);
        double yi_upper = a*exp(-(lambda+error)*ti);
        fprintf(plotting_data, "%10.4f %10.4f %10.4f %10.4f\n", ti, yi, yi_lower, yi_upper);
    }

    // Free memory
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(dy);
    gsl_vector_free(par);
    gsl_vector_free(par_err);
    gsl_matrix_free(cov);

    // close files
    fclose(x_data);
    fclose(y_data);
    fclose(y_error);

    return 0;
}
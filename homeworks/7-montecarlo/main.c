#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double plainmc(int dim, double f(int dim, double* x), double* a, double* b, int N, double *error);

// one dimentional sinc function
double sinc(int dim, double* x) {
    return sin(x[0])/x[0];
}

// three dimensional integral
double func(int dim, double* x) {
   return 1.0 / (1 - cos(x[0]) * cos(x[1]) * cos(x[2])) / (M_PI*M_PI*M_PI);
}


int main() {
    // Calculate sin(x)/x from 0 to 2pi
    int dim = 1;
    double a[1] = {0};
    double b[1] = {2.0*M_PI};
    int N = 1e6;
    double result, error;
    result = plainmc(dim, sinc, a, b, N, &error);

    printf("Result of sinx/x integrated from {0} to {2pi}: %10.10f \n", result);
    printf("Error of the sampling: %10.10f\n", error);

    printf("\n");
    printf("\n");

    // Calculate three dimensional integral from {0,0,0} to {pi,pi,pi} 
    dim = 3;
    double c[3] = {0, 0, 0};
    double d[3] = {M_PI, M_PI, M_PI};
    N = 1e6;
    result = plainmc(dim, func, c, d, N, &error);

    printf("Result of weird ass integral from {0,0,0} to {pi,pi,pi}: %10.10f \n", result);
    printf("Error of the sampling: %10.10f\n", error);
    return 0;
}
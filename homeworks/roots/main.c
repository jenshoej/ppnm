#include<stdio.h>
#include<math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_blas.h>
#include<float.h>
#include"matrix.h"

int calls;
int newton(void f(gsl_vector* x, gsl_vector* fx), gsl_vector* x, double acc);

void f(gsl_vector* x, gsl_vector* fx) {
    double y = gsl_vector_get(x, 0);
    double z = gsl_vector_get(x, 1);
    gsl_vector_set(fx, 0, -3 + 2*y*y);
    gsl_vector_set(fx, 1, -4 + 2*y + 4*z*z);
}

// The gradient of Rosenbrock's valley function, for finding its' extrema. I.e. f'(x,y) = 0 is an extremum of f(x,y)
void rosenbrock(gsl_vector* x, gsl_vector* fx) {
    calls++;
    double y = gsl_vector_get(x, 0);
    double z = gsl_vector_get(x, 1);
    gsl_vector_set(fx, 0, 2*y - 2 + 400*y*y*y - 400*y*z);
    gsl_vector_set(fx, 1, 200*z - 200*y*y);
}


int main() {

    /* -------- Task A ---------- */
    printf("------------ Task A ------------\n");
    int n = 2; // size of x vector, i.e. number of variables in f(x, y, ...)
    gsl_vector* x = gsl_vector_alloc(n);
    gsl_vector* fx = gsl_vector_alloc(n);
    
    // Initial guess
    double a = -2;
    double b = 8;
    double x_init[] = {a, b};
    for(int i = 0; i < n; i++) {
        gsl_vector_set(x, i, x_init[i]);
    }
    
    // Call root finder
    double acc = 1e-3;
    f(x, fx);
    printf("Initial guess:\n");
    print_vector(x);

    int pis = newton(rosenbrock, x, acc);

    f(x, fx);
    printf("The roots of the Rosenbrock valley function f(x,y) = (1-x)**2 + 100(y-x**2)**2 are:\n");
    print_vector(x);
    printf("And the value of the function at the roots are:\n");
    print_vector(fx);
    printf("Number of steps: %i\n", pis);
    printf("Number of calls: %i\n", calls);
    return 0;
}
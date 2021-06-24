#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<float.h>
#include<math.h>

int quasinewton(double F(gsl_vector*), gsl_vector* x, double acc);

double Rosenbrock(gsl_vector* p) {
    double x = gsl_vector_get(p, 0);
    double y = gsl_vector_get(p, 1);
    return (1 - x)*(1 - x) + 100.0*(y - x*x)*(y - x*x);
}

double Himmelblau(gsl_vector* p) {
    double x = gsl_vector_get(p, 0);
    double y = gsl_vector_get(p, 1);
    return (x*x + y - 11)*(x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
}

int main() {

    /* ------- TASK A --------- */

    /* -- Rosenbrock's valley function -- */
    printf("--- Rosenbrock's function ---\n");
    int n = 2; //nr. of params of f(x,...,x_n)
    double acc = 1e-3;
    gsl_vector* x = gsl_vector_alloc(n);

    // Initial guess
    double a = 5;
    double b = 10;
    double x_init[] = {a, b};
    for(int i = 0; i < n; i++) {
        gsl_vector_set(x, i, x_init[i]);
    }

    
    int RB = quasinewton(Rosenbrock, x, acc);
    printf("We have a minimum at:\n");
    for(int i = 0; i < n; i++) {
        printf("x%i = %g\n", i, gsl_vector_get(x,i));
    }
    printf("Number of steps to find the minimum: %i\n", RB);

    printf("\n");
    /* --- HIMMELBLAU --- */
    for(int i = 0; i < n; i++) {
        gsl_vector_set(x, i, 7);
    }
    printf("--- Himmelblaus function ---\n");
    int HB = quasinewton(Himmelblau, x, acc);
    printf("We have a minimum at:\n");
    for(int i = 0; i < n; i++) {
        printf("x%i = %g\n", i, gsl_vector_get(x,i));
    }
    printf("Number of steps to find the minimum: %i\n", HB);
    return 0;
}
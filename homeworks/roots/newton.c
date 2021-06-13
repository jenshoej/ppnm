#include<stdio.h>
#include<math.h>
#include"matrix.h"
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_blas.h>
#include<float.h>

int newton(void f(gsl_vector* x, gsl_vector* fx), gsl_vector* x, double acc) {

    // Declare necessary integers, vectors and matricies
    int n = x->size; // Dimension of vectors
    int steps = 0;
    int limit = 1e4;
    double eps = DBL_EPSILON;
    double deltax = sqrt(eps);
    gsl_vector* x_new = gsl_vector_alloc(n);
    gsl_vector* fx = gsl_vector_alloc(n);
    gsl_vector* fx_new = gsl_vector_alloc(n);
    gsl_vector* df = gsl_vector_alloc(n);
    gsl_vector* Dx = gsl_vector_alloc(n); // Big Delta x
    gsl_matrix* J = gsl_matrix_alloc(n, n);
    gsl_matrix* R = gsl_matrix_alloc(n, n);

    while(steps < limit) { // Do while number of iterations is less than 10000. And break if ||f(x)|| < eps. 
        f(x, fx); // fx holds f(x)

        /* Calculate the Jacobian matrix using finite differences */
        for(int k = 0; k < n; k++) {

            /* Find k'th element and add deltax */
            double xk = gsl_vector_get(x, k);
            gsl_vector_set(x, k, xk + deltax); // Set new x values to x + deltax

            /* df now holds f(x + deltax) */
            f(x, df); 

            /* Calculate ik'th element of Jacobian */
            for(int i = 0; i < n; i++) {
                double dfi = gsl_vector_get(df, i); // f(x + deltax)
                double fxi = gsl_vector_get(fx, i); // f(x)
                double sum = (dfi - fxi)/deltax; // Jik = [f(xk + deltax) - f(xk)] / deltaxk
                gsl_matrix_set(J, i, k, sum);
            }
            gsl_vector_set(x, k, xk);
        }

        /* Solve J*Dx = -f(x) */
        GS_decomp(J, R); // QR decomposition
        GS_solve(J, R, fx, Dx); // Result stored in Dx
        gsl_vector_scale(Dx, -1);

        /* Backtracking line search */
        /* Continue while ||f(x + lambda*x0)|| > (1-lambda/2)||f(x)|| and lambda > 1/64 */
        double lambda = 1;
        while(lambda > 1.0/64) {
            gsl_vector_memcpy(x_new, x);
            gsl_vector_add(x_new, Dx);
            f(x_new, fx_new);
            double fx_new_norm = gsl_blas_dnrm2(fx_new);
            double fx_norm = gsl_blas_dnrm2(fx);
            if(fx_new_norm > (1 - lambda*0.5)*fx_norm) break;
            lambda *= 0.5;
            gsl_vector_scale(Dx, 0.5);
        }

        // Take step and test if convergence is reached
        gsl_vector_memcpy(x, x_new);
		gsl_vector_memcpy(fx, fx_new);
        if(gsl_blas_dnrm2(Dx) < deltax || gsl_blas_dnrm2(fx) < eps) break;
        steps++;
    } // End while

    // Free memory
    gsl_vector_free(x_new);
    gsl_vector_free(fx);
    gsl_vector_free(fx_new);
    gsl_vector_free(df);
    gsl_vector_free(Dx);
    gsl_matrix_free(J);
    gsl_matrix_free(R);

    return steps;
}

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <gsl/gsl_interp.h>

double linterp(int n, double* x, double* y, double z);
double linterp_integ(int n, double x[], double y[], double z);

// data of x^2 
int n = 6;
double x[] = {0, 1, 2, 3, 4, 5};
double y[] = {0, 1, 4, 9, 16, 25};


int main() {
    // Write points to a file
    FILE* points = fopen("points.txt", "w");
    for(int i = 0; i < n; i++) {
        fprintf(points, "%10.4f %10.4f\n", x[i], y[i]);
    }

    gsl_interp* gsl_linterp = gsl_interp_alloc(gsl_interp_linear, n);
    gsl_interp_init(gsl_linterp, x, y, n);

    int N = 100;
    double stepsize = 5.0 / N;
    double z = 0;
    for(int i = 0; i <= N; i++) {
        // Implemeted linear interpolant
        double yi = linterp(n, x, y, z);
        double yi_integ = linterp_integ(n, x, y, z);

        // GSL linear interpolant
        double yi_gsl = gsl_interp_eval(gsl_linterp, x, y, z, NULL);
        double yi_gsl_integ = gsl_interp_eval_integ(gsl_linterp, x, y, x[0], z, NULL);

        // Print out values
        printf("%10.4f %10.4f %10.4f %10.4f %10.4f\n", z, yi, yi_integ, yi_gsl, yi_gsl_integ);
        z = z+stepsize;
    }

    gsl_interp_free(gsl_linterp);
    return 0;
}
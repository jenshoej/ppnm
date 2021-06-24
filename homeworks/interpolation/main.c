#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <gsl/gsl_interp.h>

// linear stuff
double linterp(int n, double* x, double* y, double z);
double linterp_integ(int n, double x[], double y[], double z);

//quadratic stuff
typedef struct {int n; double *x,*y,*b,*c;} qspline;
qspline* qspline_alloc(int n, double* x, double* y);
double qspline_eval(qspline *s, double z);
void qspline_free(qspline *s);
double qspline_integ(qspline *s, double z);
double qspline_deriv(qspline *s, double z);

// data of x^2 
int n = 6;
double x[] = {0, 1, 2, 3, 4, 5};
double y[] = {0, 1, 4, 9, 16, 25};


void linear_spline() {
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
}

void quadratic_spline() {
    qspline *s = qspline_alloc(n, x, y);
    int N = 100;
    double zmin = x[0];
    double zmax = x[n-1];
    double dz = (zmax - zmin)/N;
    double z = zmin;
    for(int i = 0; i<N; i++) {
        double qs = qspline_eval(s, z);
        double qsi = qspline_integ(s, z);
        double qsd = qspline_deriv(s, z);
        printf("%10.4f %10.4f %10.4f %10.4f\n", z, qs, qsi, qsd);
        z += dz;
    }
    qspline_free(s);
}

int main() {
    linear_spline();
    quadratic_spline();
    return 0;
}
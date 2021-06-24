#include <stdio.h>
#include <assert.h>
#include <math.h>

//quadratic stuff
typedef struct {int n; double *x,*y,*b,*c;} qspline;
qspline* qspline_alloc(int n, double* x, double* y);
double qspline_eval(qspline *s, double z);
void qspline_free(qspline *s);
double qspline_integ(qspline *s, double z);
double qspline_deriv(qspline *s, double z);

// data of y = x^2 
int n = 6;
double x[] = {0, 1, 2, 3, 4, 5};
double y[] = {0, 1, 4, 9, 16, 25};


int main() {
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
    return 0;
}
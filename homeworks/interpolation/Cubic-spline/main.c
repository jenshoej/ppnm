#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef struct {int n; double *x,*y,*b,*c,*d;} cspline;
cspline* cspline_alloc(int n, double *x, double *y);
void cspline_free(cspline *s);
double cspline_eval(cspline *s, double z);
double cspline_integ(cspline *s, double z);
double cspline_deriv(cspline *s, double z);


// points to interpolate
int n = 6;
double x[] = {0, 1, 2, 3, 4, 5};
double y[] = {0, 3, 4, 2, 5, 1};

int main() {

    cspline* s = cspline_alloc(n, x, y);
    int N = 100;
    double zmin = x[0];
    double zmax = x[n-1];
    double dz = (zmax - zmin)/N;
    double z = zmin;
    for(int i = 0; i<N; i++) {
        double qs = cspline_eval(s, z);
        double qsi = cspline_integ(s, z);
        double qsd = cspline_deriv(s, z);
        printf("%10.4f %10.4f %10.4f %10.4f\n", z, qs, qsi, qsd);
        z += dz;
    }
    cspline_free(s);

    return 0;
}


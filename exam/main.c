#include<stdio.h>
#include<math.h>


/* Akima spline stuff */
typedef struct {int n; double *x, *y, *b, *c, *d;} aspline;
aspline* aspline_alloc(int n, double *x, double *y);
double aspline_eval(aspline *as, double z);
double aspline_free(aspline *as);

/* Cubic spline stuff */
typedef struct {int n; double *x,*y,*b,*c,*d;} cspline;
cspline* cspline_alloc(int n, double *x, double *y);
double cspline_eval(cspline *cs, double z);
double cspline_free(cspline *cs);

/* Make an interpolation, like the one from the book to compare */
void spline1() {

    /* Points to interpolate */
    int n = 6;
    double xs[] = {-3.5, -2.1, -0.7, 0.7, 2.1, 3.5};
    double ys[] = {-1., -1., -1., 1., 1., 1.};

    /* Allocate splines */
    aspline *as = aspline_alloc(n, xs, ys);
    cspline *cs = cspline_alloc(n, xs, ys);
    
    /* Files for printing spline values */
    FILE* aspline_data = fopen("aspline_data_1.txt", "w");
    FILE* cspline_data = fopen("cspline_data_1.txt", "w");
    FILE* points = fopen("data_points_1.txt", "w");
    for(int i = 0; i < n; i++) {
        fprintf(points, "%g %g\n", xs[i], ys[i]);
    }

    /* Evaluate the spline at many points */
    int N = 100;
    double z;
    double zmin = xs[0];
    double zmax = xs[n-1];
    double dz = (zmax - zmin)/N;
    z = zmin; // set initial z value
    for(int i = 0; i < N; i++) {
        double aspline = aspline_eval(as, z);
        fprintf(aspline_data, "%10.5f %10.5f\n", z, aspline);
        z += dz;
    }
    z = zmin;
    for(int i = 0; i < N; i++) {
        double cspline = cspline_eval(cs, z);
        fprintf(cspline_data, "%10.5f %10.5f\n", z, cspline);
        z += dz;
    }
    aspline_free(as);
    cspline_free(cs);
}

/* make a random interpolation, with jumps in the data */

void spline2() {
        /* Points to interpolate */
    int n = 10;
    double xs[] = {0., 2., 4., 6., 8., 10., 12., 14., 16., 18.};
    double ys[] = {2., 3., 3.5, 4., 10., 5., 6., 6.5, -2., 4.};

    /* Allocate splines */
    aspline *as = aspline_alloc(n, xs, ys);
    cspline *cs = cspline_alloc(n, xs, ys);
    
    /* Files for printing spline values */
    FILE* aspline_data = fopen("aspline_data_2.txt", "w");
    FILE* cspline_data = fopen("cspline_data_2.txt", "w");
    FILE* points = fopen("data_points_2.txt", "w");
    for(int i = 0; i < n; i++) {
        fprintf(points, "%g %g\n", xs[i], ys[i]);
    }

    /* Evaluate the spline at many points */
    int N = 100;
    double z;
    double zmin = xs[0];
    double zmax = xs[n-1];
    double dz = (zmax - zmin)/N;
    z = zmin; // set initial z value
    for(int i = 0; i < N; i++) {
        double aspline = aspline_eval(as, z);
        fprintf(aspline_data, "%10.5f %10.5f\n", z, aspline);
        z += dz;
    }
    z = zmin;
    for(int i = 0; i < N; i++) {
        double cspline = cspline_eval(cs, z);
        fprintf(cspline_data, "%10.5f %10.5f\n", z, cspline);
        z += dz;
    }
    aspline_free(as);
    cspline_free(cs);
}

int main() {
    printf("Thank you for a great course :)\n");
    spline1();
    spline2();
    return 0;
}
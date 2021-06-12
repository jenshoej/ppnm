#include <stdio.h>
#include <math.h>
#include <assert.h>

 
double x_i[] = {1.0/6, 2.0/6, 4.0/6, 5.0/6}; // Abssicas, for easy re use when subdividing intervals
double w_i[] = {2.0/6, 1.0/6, 1.0/6, 2.0/6}; // Weigths (trapezium rule)
double v_i[] = {1.0/4, 1.0/4, 1.0/4, 1.0/4}; // Weights for error estimate (rectangle rule)

double adapt24(double f(double), double a, double b, double acc, double eps, double f2, double f3, int limit ){

    assert (limit < 1e5);

    // Calculate end points
    double f1 = f(a + (b-a) * x_i[0]);
    double f4 = f(a + (b-a) * x_i[3]);

    // Calculate the 2. and 4. order estimate and the tolerance and error
    double Q = (2 * f1 + f2 + f3 + 2 * f4) / 6 * (b-a); 
    double q = (f1 + f4 + f2 + f3) / 4 * (b-a);
    double tolerance = acc + eps * fabs(Q);
    double error = fabs(Q-q);

    // Check if step is accepted or rejected
    if (error < tolerance) { return Q; }
    else { //subdivide if rejected
        double Q1 = adapt24(f, a, (a+b)/2, acc/sqrt(2.0), eps, f1, f2, limit+1); 
        double Q2 = adapt24(f, (a+b)/2, b, acc/sqrt(2.0), eps, f3, f4, limit+1); 
        return Q1 + Q2; 
    }
}
double quad(double f(double), double a, double b, double acc, double eps) {
    // Calculate middle points 
    double f2 = f(a + 2 * (b-a) / 6);
    double f3 = f(a + 4 * (b-a) / 6); 
    int limit = 0;
    return adapt24(f, a, b, acc, eps, f2, f3, limit); 
}


// Curtis Clenshaw transformation of the integral

double (*cc_func)(double);
double cc_a, cc_b;
double cc_wrapper(double x) {
    return cc_func((cc_a + cc_b)/2 + (cc_b - cc_a)*cos(x)/2)*(cc_b - cc_a)*sin(x)/2;
}

double quadCC(double f(double), double a, double b, double acc, double eps){
    cc_func = f;
    cc_a = a;
    cc_b = b;
    return quad(cc_wrapper, 0, M_PI, acc, eps);  
}

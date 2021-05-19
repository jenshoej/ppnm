#include <stdio.h>
#include <math.h>
#include <assert.h>

double quad(double f(double), double a, double b, double acc, double eps); // Header for quadrature function

double sqrt_x(double x) { 
    return sqrt(x); 
}

double weird_function(double x) {
    return 4 * sqrt(1 - x*x);
}

int main() {
    double quad1 = quad(sqrt_x, 0, 1, 0.001, 0.001);
    printf("Value of the integral of sqrt(x)dx from 0 to 1 is (should be 2/3) %10.3f\n", quad1);
    
    double quad2 = quad(weird_function, 0, 1, 0.001, 0.001);
    printf("Value of the integral of 4*sqrt(1-x^2)dx from 0 to 1 is (should be pi) %10.3f\n", quad2);
    return 0;
}
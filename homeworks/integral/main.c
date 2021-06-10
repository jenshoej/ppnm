#include <stdio.h>
#include <math.h>
#include <assert.h>

double quad(double f(double), double a, double b, double acc, double eps); // Header for quadrature function

int calls;
double pi = 3.14159265359;

double sqrt_x(double x) { 
    calls++;
    return sqrt(x); 
}

double weird_function(double x) {
    calls++;
    return 4 * sqrt(1 - x*x);
}

int main() {
    calls = 0;
    double quad1 = quad(sqrt_x, 0, 1, 0.001, 0.001);
    printf("Value of the integral of sqrt(x)dx from 0 to 1 is (should be 2/3) %10.10f\n", quad1);
    printf("Number of calls: %10i\n", calls);
    
    printf("\n");
    calls = 0;
    double quad2 = quad(weird_function, 0, 1, 0.001, 0.001);
    printf("Value of the integral of 4*sqrt(1-x^2)dx from 0 to 1 is (should be pi = 3.14159265359) %10.10f\n", quad2);
    printf("Number of calls: %10i\n", calls);
    return 0;
}
#include <stdio.h>
#include <math.h>
#include <assert.h>

double quad(double f(double), double a, double b, double acc, double eps); // Header for quadrature function
double quadCC(double f(double), double a, double b, double acc, double eps);

int calls;
double pi = 3.14159265359;

double sqrt(double x) { 
    calls++;
    return sqrt(x); 
}

double weird_function(double x) {
    calls++;
    return 4 * sqrt(1 - x*x);
}

double inverse_sqrt(double x) {
    calls++;
    return 1.0/sqrt(x);
}

double log_inverse_sqrt(double x) {
    calls++;
    return log(x)/sqrt(x);
}


int main() {

/* -------- PART A ----------- */

    printf("PART A\n");
    printf("\n");
    printf("Adaptive 24 integration routine\n");
    printf("\n");
    calls = 0;
    double quad1 = quad(sqrt, 0, 1, 0.001, 0.001);
    printf("Value of the integral of sqrt(x)dx from 0 to 1 is (should be 2/3) %10.10f\n", quad1);
    printf("Number of calls: %10i\n", calls);
    
    printf("\n");
    calls = 0;
    double quad2 = quad(weird_function, 0, 1, 0.00001, 0.00001);
    printf("Value of the integral of 4*sqrt(1-x^2)dx from 0 to 1 is (should be pi = 3.14159265359) %10.15f\n", quad2);
    printf("Number of calls: %10i\n", calls);
    printf("\n");
/* -------- PART B ----------- */

    printf("PART B\n");
    printf("\n");
    printf("Curtis Clenshaw 24 integration routine\n");
    printf("\n");
    calls = 0;
    double quad3 = quadCC(inverse_sqrt, 0, 1, 0.001, 0.001);
    printf("Value of the integral of 1/sqrt(x) from 0 to 1 is (should be 2) %10.10f\n", quad3);
    printf("Number of calls: %10i\n", calls);

    printf("\n");
    calls = 0;
    double quad4 = quadCC(log_inverse_sqrt, 0, 1, 0.001, 0.001);
    printf("Value of the integral of ln(x)/sqrt(x) from 0 to 1 is (should be -4) %10.10f\n", quad4);
    printf("Number of calls: %10i\n", calls);

    printf("\n");
    calls = 0;
    double quad5 = quadCC(weird_function, 0, 1, 0.00001, 0.00001);
    printf("Value of the integral of 4*sqrt(1-x^2)dx from 0 to 1 is (should be pi = 3.14159265359) %10.15f\n", quad5);
    printf("Number of calls: %10i\n", calls);

    return 0;
}
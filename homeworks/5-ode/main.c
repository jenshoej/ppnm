#include <stdio.h>
#include <math.h>

void rkstep23( void (*f)(int n, double t, double* y, double* dydt), double t, double* yt, double* y_next, double h, double* err );

int driver( 
    void (*f)(int n, double t, double* y, double* dydt),
    int n,
    int a,
    int b,
    double* y_init,
    double* ys,
    double h,
    double eps,
    double acc,
    char* points );

// Right hand side of dy/dt = f(t, y)
void fun(int n, double t, double* y, double* dydt) {
        dydt[0] = y[1];
        dydt[1] = -y[0];
}

double N, Tc, Tr;
void SIR_func(int n, double t, double* y, double* dydt) {
    dydt[0] = -y[1]*y[0]/(N*Tc);
    dydt[1] = y[1]*y[0]/(N*Tc) - y[1]/Tr;
    dydt[2] = y[1]/Tr;
}


void second_order() {
    // Try and solve u'' = -u: 
    // Change second order ODE to two first order ODEs.
    // y0 = u
    // y1 = u'
    // y0' = y1
    // y1' = -y0

    int n = 2, a = 0, b = 2*M_PI;
    double y_init[n];
    double ys[n];
    double h = 0.1, acc = 0.0001, eps = 0.0001;
    char* points = "second-order-test.txt";

    // Set initial values
    y_init[0] = 1;
    y_init[1] = 0;

    // Call driver
    int ode = driver(fun, n, a, b, y_init, ys, h, eps, acc, points);
    printf("Number of steps of u'' = -u %d\n", ode);
}

void SIR() {
    // Solve SIR model

    int n = 3, a = 0, b = 60;
    double y_init[n];
    double ys[n];
    double h = 0.1, acc = 1, eps = 0.0001;
    char* points = "SIR.txt";

    // Set initial values
    N = 5800000;
    Tc = 1.5;
    Tr = 7.0;

    y_init[0] = N;
    y_init[1] = 50;
    y_init[2] = 0;

    // Call driver
    int ode = driver(SIR_func, n, a, b, y_init, ys, h, eps, acc, points);
    printf("Number of steps of SIR model %d", ode);

}

int main() {
    second_order();
    SIR();
    return 0;
}




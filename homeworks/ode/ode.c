#include <stdio.h>
#include <math.h>
#include <gsl/gsl_vector.h>

// Laver en stepper der benytter Bogacki-Shampine metoden
void rkstep23( void (*f)(int n, double t, double* y, double* dydt), int n, double t, double* yt, double* y_next, double h, double* err ) {				                 

    double k1[n], k2[n], k3[n], k4[n], y_temp[n]; // Declare variables. kn's = f(t, y). y_temp is for storing temporary values for y(t) to estimate error

    f(n, t, yt, k1); // k1 = f(t, y)
    for(int i = 0; i < n; i++) {
        y_temp[i] = yt[i] + (1.0/2)*k1[i]*h;
    }

    f(n, t + (1.0/2)*h, y_temp, k2); // k2 = f(t + 1/2h, y + h*(1/2*k1))
    for(int i = 0; i < n; i++) {
        y_temp[i] = yt[i] + (3.0/4)*h*k2[i];
    }

    f(n, t + (3.0/4)*h, y_temp, k3); // k3 = f(t + 3/4*h, y + h*(3/4)*k2)
    for(int i = 0; i < n; i++) {
        y_next[i] = yt[i] + ( (2.0/9)*k1[i] + (1.0/3)*k2[i] + (4.0/9)*k3[i] )*h;
    }

    f(n, t + h, y_next, k4);
    for(int i = 0; i < n; i++) {
        y_temp[i] = yt[i] + ( (7.0/24)*k1[i] + (1.0/4)*k2[i] + (1.0/3)*k3[i] + (1.0/8)*k4[i] )*h;
        err[i] = y_next[i] - y_temp[i];
    }

}

int driver(
    void (*f)(int n, double t, double* y, double* dydt), // RHS of dy/dt = f(t, y)
    int n,          // Size of vectors
    int a,          // Start point
    int b,          // End point
    double* y_init, // y(a): initial values
    double* ys,     // y values throughout integration
    double h,       // Initial step size
    double rel,     // Relative accuracy goal
    double abs,     // Absolute accuracy goal
    char* file )    //Output file
{
    // More variables
    int steps = 0; // Step counter
    double t;      // Current t
    double y[n];   // Current y vector. y vector holds the RHS of system of linear equations.
    double yh[n];  // Estimate of y(t + h)
    double err[n]; // Error estimate vector
    double tau;    // Local tolerance
    FILE *points = fopen(file, "w");

    t = a; // Start of integration
    fprintf(points, "%10f", t);
    for (int i = 0; i < n; ++i) {
        y[i] = y_init[i]; // Initial values
        fprintf(points, "%10f", y[i]); // Write y values to outfile
    }
    fprintf(points, "\n");

    
    while(t < b) {

        // avoid overstepping
        if (t + h > b) {
            h = b - t;
        }
        rkstep23(f, n, t, y, yh, h, err);

        // Calculate the error
        double sum = 0;
        for(int i = 0; i < n; i++) {
            sum += err[i]*err[i];
        }
        double e = sqrt(sum);

        // The local tolerance is tau_i = (rel*||y_i|| + abs)*sqrt(h_i/(b-a))
        double sum2 = 0;
        for(int i = 0; i < n; i++) { // Calculating ||y_i||
            sum2 += y[i]*y[i];
        }
        double y_norm = sqrt(sum2);
        tau = (rel*y_norm + abs)*sqrt(h/(b - a));

        // Step is rejected if e > t
        if(e < tau) {
            steps++; // Increase number of steps
            t = t + h; // Move t forward 
            fprintf(points, "%10f", t);
            for(int i = 0; i < n; ++i) { // Update y values
                y[i] = yh[i];
                fprintf(points, "%10f", y[i]);
            }
            fprintf(points, "\n");
        }
        if (e > 0) { h *= pow(tau/e, 0.25)*0.95; }
        else { h *= 2; } 
        
    } // End while
    return steps;
}



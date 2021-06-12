#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define RND (double)rand()/RAND_MAX


double plainmc(int dim, double f(int dim, double* x), double* a, double* b, int N, double *error) {
	// Calculate the volume
    double V = 1; 
    for(int i = 0; i < dim; i++) {
        V *= b[i] - a[i];
    }
    // Sample function at random
	double sum = 0;
    double sum2 = 0;
    double x[dim];
    double fx;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < dim; j++) {
            x[j] = a[j] + RND*(b[j] - a[j]);
        }
		fx = f(dim, x);
		sum += fx;
		sum2 += fx * fx;
    }

    // Calculate error and result
	double mean = sum/N; // Mean
    double sigma = sqrt(sum2/N - mean*mean); // Standard deviation
	double result = mean*V + I*sigma*V/sqrt(N);
    *error = V*sigma/sqrt(N); // Error estimate
	return result;
} 
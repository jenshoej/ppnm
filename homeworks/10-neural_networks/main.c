#include<math.h>
#include<stdio.h>
#include<gsl/gsl_vector.h>

typedef struct {
	int n;
	double (*f)(double);
    double (*integ)(double);
    double (*deriv)(double);
	gsl_vector* params;
	} ann;

double ann_response(ann* network, double x);
double ann_response_integ(ann* network, double x);
double ann_response_deriv(ann* network, double x);
void ann_learn(ann* network, gsl_vector* xs, gsl_vector* ys);
void ann_free(ann* network);
ann* ann_alloc(int n, double(*f)(double), double(*integ)(double), double(*deriv)(double));

// Activation function
double Gauss_activation_function(double x) {
    return x*exp(-x*x);
}

double Gauss_activation_integ(double x) {
    return -0.5*exp(-x*x);
}

double Gauss_activation_deriv(double x) {
    return (1 - 2*x*x)*exp(-x*x);
}

double fitting_function(double x) {
    return 5*cos(x-1)*exp(-x*x);
}

int main() {

    int n = 4;
    ann* network = ann_alloc(n, Gauss_activation_function, Gauss_activation_integ, Gauss_activation_deriv);

    // Generate datapoints to run the ANN on
    int N = 50;
	gsl_vector* xs = gsl_vector_alloc(N);	
	gsl_vector* ys = gsl_vector_alloc(N);	
	double a = -1;
    double b = 3;
    double dx = (b - a)/(N - 1);
    double x;
	x = a;
	for(int i = 0; i < N; i++) {
		gsl_vector_set(xs, i, x);
		gsl_vector_set(ys, i, fitting_function(x));
		x += dx;
	}

    // Set initial values of parameters
	for(int i = 0; i < network->n; i++){
		gsl_vector_set(network->params, 3*i, a + (b - a)*i/(network->n - 1));
		gsl_vector_set(network->params, 3*i+1, 1);
		gsl_vector_set(network->params, 3*i+2, 1);
	}

    // Train the network
    ann_learn(network, xs, ys);

    // Write points for plotting
    for(int i = 0; i < xs->size; i++) {
		double x = gsl_vector_get(xs, i);
		double y = gsl_vector_get(ys, i);
		printf("%10.6f %10.6f\n", x, y);
	}

    printf("\n\n");
    // Iterate the network response at many points
	double z = a;
    double dz = dx;
	for(int i = 0; i < N; i++) {
		double ann_eval = ann_response(network, z);
        double ann_integ = ann_response_integ(network, z);
        double ann_deriv = ann_response_deriv(network, z);
		printf("%10.6f %10.6f %10.6f %10.6f\n", z, ann_eval, ann_integ, ann_deriv);
		z += dz;
	}

    ann_free(network);
    gsl_vector_free(xs);
    gsl_vector_free(ys);

    return 0;
}

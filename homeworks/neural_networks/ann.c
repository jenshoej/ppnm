#include<gsl/gsl_vector.h>
#include<math.h>

typedef struct {
	int n;
	double (*f)(double);
    double (*f_integ)(double);
    double (*f_deriv)(double); 
	gsl_vector* params;
	} ann;

ann* ann_alloc(int n, double(*f)(double), double(*integ)(double), double(*deriv)(double)) {
	ann* network = malloc(sizeof(ann));
	network->n = n;
	network->f = f;
    network->f_integ = integ;
    network->f_deriv = deriv;
	network->params = gsl_vector_alloc(3*n);
	return network;
}

void ann_free(ann* network){
	gsl_vector_free(network->params);
	free(network);
}

double ann_response(ann* network, double x) {
	double y = 0;
	for(int i = 0; i < network->n; i++){
		double a = gsl_vector_get(network->params, 3*i);
		double b = gsl_vector_get(network->params, 3*i+1);
		double w = gsl_vector_get(network->params, 3*i+2);
		y += network->f((x - a)/b)*w;
	}
	return y;
}

int quasinewton(double F(gsl_vector*), gsl_vector*x, double acc);

void ann_learn(ann* network, gsl_vector* xs, gsl_vector* ys) {
	double cost_func(gsl_vector* p) {
		gsl_vector_memcpy(network->params, p);
		double sum = 0;
        int N = xs->size;
		for(int i = 0; i < N; i++) {
			double xi = gsl_vector_get(xs, i);
			double yi = gsl_vector_get(ys, i);
			double Fi = ann_response(network, xi);
			sum += (Fi - yi)*(Fi - yi);
		}
		return sum;
	}
    double accu = 1e-3;
	gsl_vector* p = gsl_vector_alloc(network->params->size);
	gsl_vector_memcpy(p, network->params);
	int min = quasinewton(cost_func, p, accu); // minimize the cost function
	gsl_vector_memcpy(network->params, p);
	gsl_vector_free(p);
}


double ann_response_integ(ann* network, double x) {
	double y = 0;
	for(int i = 0; i < network->n; i++) {
		double a = gsl_vector_get(network->params, 3*i);
		double b = gsl_vector_get(network->params, 3*i+1);
		double w = gsl_vector_get(network->params, 3*i+2);
		y += b*w*network->f_integ((x - a)/b);
	}
	return y;
}


double ann_response_deriv(ann* network, double x) {
	double y = 0;
	for(int i = 0; i < network->n; i++) {
		double a = gsl_vector_get(network->params, 3*i);
		double b = gsl_vector_get(network->params, 3*i+1);
		double w = gsl_vector_get(network->params, 3*i+2);
		y += w*network->f_deriv((x-a)/b)/b;	
	}
	return y;
}
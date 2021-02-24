#include <stdio.h>
#include <math.h>
#include <gsl/gsl_sf_gamma.h>

int main() {
	double xmin = -5, xmax = 5;
	for(double x = xmin; x<= xmax; x+= 1.0/2) {
		printf("%10g %10g \n", x, gsl_sf_gamma(x));
	}
	return 0;
}

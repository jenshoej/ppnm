#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

/* create the function */
double f(double x, void* params) {
	return log(x)/sqrt(x);
}

/* create a routine for integrating a function from a to b */
double integral(int a, int b) {
	gsl_function F; // Integration routine must work with a gsl_function
	F.function=&f; // Set gsl_function to the adress of our function f
	int limit = 999; // Maximum number of steps of integration
	gsl_integration_workspace* w; // dunno wtf this shit is
	w = gsl_integration_workspace_alloc(limit);

	/* declare and initialize variables */
	double result; //variable to store the result
	double abserr; //variable to store the error
	double epsabs = 1e-6;
	double epsrel = 1e-6;

	/* sove integral using qags routine */
	gsl_integration_qags(&F,a,b,epsabs,epsrel,limit,w,&result,&abserr); //do the intergration
	gsl_integration_workspace_free(w); // free the memory of the workspace
	return result;
}

int main() {
	/* Calculate the integral of Task A from 0 to 1 */
	double res = integral(0,1);
	printf("Result of the integral is = %g\n", res);
return 0;
}

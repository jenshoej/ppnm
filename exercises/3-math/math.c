#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {

	// Task 1

	double pi = M_PI;
	double e = M_E;

	//Squareroot of negative 2
	double complex z = csqrt(-2);
	printf("Real part of sqrt(-2): %f\n",creal(z));
	printf("imaginary part of sqrt(-2): %f\n", cimag(z));

	//Exp(I)
	double complex n = cpow(e, I);
	printf("Real part of e^i: %f\n", creal(n));
	printf("imaginary part of e^i: %f\n", cimag(n));
	//Exp(I*pi)

	double p = exp(I*pi);
	printf("%f\n", p);
	//Nogle sinusværdier
	printf("sin(pi/6) = %f\n", sin(pi/6));
	printf("sin(pi/3) = %f\n", sin(pi/3));

	// Gammafunction
	double g = tgamma(5);
	printf("Value of the gammafunction of 5 = %g\n", g);

	double b = j0(0.5);
	printf("Value of the bessel function of 0.5 = %g\n", b);

	// Task 2

	float x_float = 1.f/9;
	double x_double = 1./9;
	long double x_long_double = 1.L/9;

	printf("Float %.25g\n", x_float);

	printf("Float %.25lg\n", x_double);

	printf("Double %.25Lg\n", x_long_double);
	return 0;
}

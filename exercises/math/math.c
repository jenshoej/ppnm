#include <stdio.h>
#include <math.h>
#include <complex.h>

int main() {
	double pi = M_PI;
	double e = M_E;

	//Squareroot of negative 2
	double complex z = I * sqrt(2);
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
	return 0;
}

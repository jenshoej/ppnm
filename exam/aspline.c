#include <stdlib.h>
#include <assert.h>
#include <math.h>
typedef struct {int n; double *x, *y, *b, *c, *d;} aspline;


aspline* aspline_alloc(int n, double *x, double *y) {
    // delta x and delta y, and p = delta y / delta x, i.e. the linear slope
    assert(n > 2); 
    double Dx[n-1];
    double p[n-1];
    for(int i = 0; i < n-1; i++) {
        Dx[i] = x[i+1] - x[i];
        assert(Dx[i] > 0);
    }
    for(int i = 0; i < n-1; i++) {
        p[i] = (y[i+1] - y[i])/Dx[i];
    }
    /* Allocate necesarry things */
    aspline *s = (aspline*)malloc(sizeof(aspline));
    // Coefficients
	s->b = (double*)malloc((n)*sizeof(double));
	s->c = (double*)malloc((n-1)*sizeof(double));
	s->d = (double*)malloc((n-1)*sizeof(double));
    // Data
	s->x = (double*)malloc(n*sizeof(double));
	s->y = (double*)malloc(n*sizeof(double));
	s->n = n;
	// Fill data into spline
	for(int i = 0; i < n; i++){
		s->x[i] = x[i];
        s->y[i] = y[i];
	}

    // First two and last two points need the special conditions (36)
    s->b[0] = p[0];
    s->b[1] = (p[0] + p[1])/2;
    s->b[n-1] = p[n-2];
    s->b[n-2] = (p[n-2] + p[n-3])/2;

    // Calculate the remaining b's from (33). The weights w are given as w[i] = |p[i] - p[i-1]|
    for(int i = 2; i < n-2; i++) {
        double w1 = fabs(p[i+1] - p[i]);
        double w2 = fabs(p[i-1] - p[i-2]); 
        if(w1 + w2 == 0) {
            s->b[i] = (p[i] + p[i-1])/2;
        }
        else {
            s->b[i] = (w1*p[i-1] + w2*p[i])/(w1+w2);
        }
    }
    // Calculate the c's and d's from (32)
    for(int i=0; i<n-1; ++i) {
		s->c[i] = (3*p[i] - 2*s->b[i] - s->b[i+1])/Dx[i];
        s->d[i] = (s->b[i] + s->b[i+1] - 2*p[i])/(Dx[i]*Dx[i]);
	}
	return s;
}

/* Function to evaluate the akima spline at each step i */
double aspline_eval(aspline *s, double z) {
    assert(z >= s->x[0] && z <= s->x[s->n-1]);
    // Binary search for the interval in which z lies
	int i = 0;
    int j = s->n-1;
	while(j - i > 1) {
		int mid = (i + j)/2;
		if(z > s->x[mid]) {
            i = mid;
        }
		else { j = mid; }
	}
    double Dx = z - s->x[i]; // (x-xi)
    /* Return the subspline Ai = a + b*(x-xi) + c*(x-xi)^2 + d*(x-xi)^3 */
    return s->y[i] + Dx*s->b[i] + Dx*Dx*s->c[i] + Dx*Dx*Dx*s->d[i];
}

/* Used to free the memory of the spline */
void aspline_free(aspline *s) {
    free(s->x);
    free(s->y);
    free(s->b);
    free(s->c);
    free(s->d);
    free(s);
}

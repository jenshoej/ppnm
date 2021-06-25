#include<stdio.h>
#include<math.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<float.h>

static const double eps = 2.22045e-16;

void numeric_gradient(double F(gsl_vector*), gsl_vector*x, gsl_vector*grad) {
	double fx = F(x);
	for(int i = 0; i < x->size; i++){
		double dx;
		double xi = gsl_vector_get(x, i);
		if(fabs(xi) < sqrt(sqrt(eps))) {
			dx = sqrt(eps);
		}
		else dx = fabs(xi)*sqrt(eps);
		gsl_vector_set(x, i, xi+dx);
		gsl_vector_set(grad, i, (F(x)-fx)/dx);
		gsl_vector_set(x, i, xi);
	}
}

int quasinewton(double F(gsl_vector*), gsl_vector*x, double acc) {
    
    // Allocate matrices and vectors
	int n = x->size, nsteps = 0, nbad = 0, ngood = 0;
	gsl_matrix* B = gsl_matrix_alloc(n, n);
	gsl_vector* gradient = gsl_vector_alloc(n);
	gsl_vector* Dx = gsl_vector_alloc(n);
	gsl_vector* z = gsl_vector_alloc(n);
	gsl_vector* gz = gsl_vector_alloc(n);
	gsl_vector* y = gsl_vector_alloc(n);
	gsl_vector* u = gsl_vector_alloc(n);
	gsl_vector* a = gsl_vector_alloc(n);
	gsl_matrix_set_identity(B);
	numeric_gradient(F, x, gradient);
	double fx = F(x);
	double fz;

	// Start sequence
	int max_steps = 1e3;
	while(nsteps < max_steps) {
		nsteps++;
		gsl_blas_dgemv(CblasNoTrans, -1, B, gradient, 0, Dx); /* Calculate hessian matrix times gradient of x */
		if(gsl_blas_dnrm2(Dx) < sqrt(eps) * gsl_blas_dnrm2(x)) { break; }
		if(gsl_blas_dnrm2(gradient) < acc)
			{ break; }
		double lambda=1;

		// Do the line search
		while(1) {
			gsl_vector_memcpy(z, x);
			gsl_vector_add(z, Dx);
			fz = F(z);
			double sTg; gsl_blas_ddot(Dx, gradient, &sTg);

			// Check for the Armijo condition
			if(fz < fx + 0.01*sTg) { 
				ngood++; break; 
			}
			if(lambda<sqrt(eps)) {
				nbad++;
				gsl_matrix_set_identity(B);
				break;
			}
			lambda *= 0.5;
			gsl_vector_scale(Dx, 0.5);
		}

		numeric_gradient(F, z, gz);
		gsl_vector_memcpy(y, gz);
		gsl_blas_daxpy(-1, gradient, y); /* y=grad(x+s)-grad(x) */
		gsl_vector_memcpy(u, Dx); /* u=s */
		gsl_blas_dgemv(CblasNoTrans, -1, B, y, 1, u); /* u=s-By */
		double sTy, uTy;
		gsl_blas_ddot(Dx,y, &sTy);

		if(fabs(sTy) > 1e-6){ // symmetric Broyden's update
			gsl_blas_ddot(u, y, &uTy);
			double gamma = uTy/2/sTy;
			gsl_blas_daxpy(-gamma, Dx, u); // u=u-gamma*s
			gsl_blas_dger(1.0/sTy, u, Dx, B); // B= B + u*s^T/s^T*y
			gsl_blas_dger(1.0/sTy, Dx, u, B); // B= B + s*u^T/s^T*y
		}
		// Set the new values of x and f(x)
		gsl_vector_memcpy(x, z);
		gsl_vector_memcpy(gradient, gz);
		fx = fz;
	}

	// Free memory
	gsl_matrix_free(B);
	gsl_vector_free(gradient);
	gsl_vector_free(Dx);
	gsl_vector_free(z);
	gsl_vector_free(gz);
	gsl_vector_free(y);
	gsl_vector_free(u);
	gsl_vector_free(a);
	//fprintf(stderr,"Quasinewton method stats: nsteps = %i ngood = %i nbad = %i fx = %.1e\n", nsteps, ngood, nbad, fx);
	return nsteps;
}
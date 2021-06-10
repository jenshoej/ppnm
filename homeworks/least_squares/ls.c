#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

// Back substitution to solve R*c = Q^Tb for c
void backsub(gsl_matrix* U, gsl_vector* c) { 
	int n = U->size1;
	for(int i = n-1; i>=0; i--) {
		double s = gsl_vector_get(c, i);
		for(int k = i+1; k<n; k++) {
			s -= gsl_matrix_get(U, i, k)*gsl_vector_get(c,k); 
		} 
		gsl_vector_set(c, i, s/gsl_matrix_get(U,i,i));
	}
}

// QR decomposition by Gram-Schmidt orthogonalization
void GS_decomp(gsl_matrix *A, gsl_matrix *R) {
	int n = A->size1;
	int m = A->size2;

	for(int i = 0; i<m; i++) {

		gsl_vector_view ai = gsl_matrix_column(A, i);

		double Rii = gsl_blas_dnrm2(&ai.vector); // Rii = sqrt(ai*ai)
		gsl_matrix_set(R, i, i, Rii);

		gsl_vector_scale(&ai.vector, 1/Rii); // qi = ai/Rii

		for(int j = i+1; j<m; j++) {
		
			gsl_vector_view aj = gsl_matrix_column(A, j);

			double Rij = 0;
			gsl_blas_ddot(&ai.vector, &aj.vector, &Rij); // Rij = qi*aj
			gsl_matrix_set(R, i, j, Rij);

			gsl_blas_daxpy(-Rij, &ai.vector, &aj.vector); // aj = aj - qi*Rij
		}
	}
}
	// Solve Rx = Q^Tb
void GS_solve(gsl_matrix *Q, gsl_matrix *R, gsl_vector *b, gsl_vector *x) {
	gsl_blas_dgemv(CblasTrans,1,Q,b,0,x); // Calculates Q^T*b
	backsub(R, x);
}

void inverse(gsl_matrix* Q, gsl_matrix* R, gsl_matrix* B) {
	int n = Q->size1;
	gsl_vector* e = gsl_vector_alloc(n);
	gsl_vector* x = gsl_vector_alloc(n);
	for(int i = 0; i < n; i++) {
		gsl_vector_set(e, i, 1.0);
		GS_solve(Q, R, e, x);
		gsl_vector_set(e, i, 0);
		gsl_matrix_set_col(B, i, x);
	}
}


// f is the function passed as an argument
// x is the x data, y is the y data, y_err is the error in y
// par, cov is the optimal parameters and the covariance matrix
// par_err is the errors in the parameters
void least_squares(int m, double (*F)(int, double), gsl_vector *x, gsl_vector *y, gsl_vector *y_err, gsl_vector *par, gsl_vector *par_err, gsl_matrix *cov) {
    
    // Allocate memory
    int n = x->size;
    gsl_matrix* A = gsl_matrix_alloc(n, m);
    gsl_matrix *R = gsl_matrix_alloc(m, m);
    gsl_vector *b = gsl_vector_alloc(n);
	gsl_matrix *R_inv = gsl_matrix_alloc(m, m);

    // Vector b = yi/dyi    
    // Matrix A = f_k(x_i)/dy_i
    for(int i = 0; i < n; i++) {
        double xi = gsl_vector_get(x, i);
        double yi = gsl_vector_get(y, i);
        double y_erri = gsl_vector_get(y_err, i);
        gsl_vector_set(b, i, yi/y_erri);
        for(int k = 0; k < m; k++) {
            gsl_matrix_set(A, i, k, F(k, xi)/y_erri);
        }
    }

    // Decompose A into QR
    GS_decomp(A, R);

    // Solve for c in Rc = Q^Tb
    GS_solve(A, R, b, par);

	// Calculate the covariance matrix as R^-1 * (R^-1)^T
	gsl_matrix_set_identity(cov);
	inverse(cov, R, R_inv);
	gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1, R_inv, R_inv, 0, cov);

	// Errors in the optimal parameters are then the square root of the diagonal elements in the covariance matrix 
 	double covkk;
    for(int k = 0; k < m; k++) {
    	covkk = gsl_matrix_get(cov, k, k);
		gsl_vector_set(par_err, k, sqrt(covkk));
    }


}


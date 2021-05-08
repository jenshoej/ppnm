#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <assert.h>

void print_vector(gsl_vector* v) {
	for(int i = 0; i < v->size; i++) {
		printf("%10.4f", gsl_vector_get(v,i));
		printf("\n");
	}
	printf("\n");
}
void print_matrix(gsl_matrix* m) {
	for(int i = 0; i < m->size1; i++){
		for(int j = 0; j < m->size2; j++) {
			printf("%10.4f",gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
	printf("\n");
}

void generate_vector(gsl_vector* v) {
	for(int i = 0; i< v->size; i++) {
		gsl_vector_set(v, i, 1.0*rand()/RAND_MAX);
	}
}

void generate_matrix(gsl_matrix* A) {
	for(int i = 0; i< A->size1; i++) {
		for(int j=0; j<A->size2; j++) {
			gsl_matrix_set(A,i,j, 1.0*rand()/RAND_MAX);
		}
	}
}

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
	
void GS_decomp(gsl_matrix *A, gsl_matrix *R) {
	// QR decomposition by Gram-Schmidt orthogonalization
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

void GS_solve(gsl_matrix *Q, gsl_matrix *R, gsl_vector *b, gsl_vector *x) {
	/* Solve QRx = b => Rx = Q^Tb */
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
	gsl_vector_free(e);
	gsl_vector_free(x);
}
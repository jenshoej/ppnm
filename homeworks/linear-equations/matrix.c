#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <assert.h>

void print_vector(gsl_vector* v) {
	for(int i = 0; i < v->size; i++) {
		printf("%10g", gsl_vector_get(v,i));
		printf("\n");
	}
}
void print_matrix(gsl_matrix* m) {
	for(int i = 0; i < m->size1; i++){
		for(int j = 0; j < m->size2; j++) {
			printf("%10g",gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
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

double in_prod(gsl_vector* a, gsl_vector* b) {
	double res;
	res = gsl_blas_ddot(a, b, &res);
	return res;
}

double norm(gsl_vector* a) {
	return sqrt(in_prod(a,a));
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



void GS_decomp(gsl_matrix* A, gsl_matrix* R) {
	int n = A->size1;
	int m = A->size2;
	 assert(R->size1==R->size2 && R->size1 == m);
	 assert(n>=m);
	// Gram-Schmidt orthogonalization A = QR, where R is a rectangular matrix, and Q is an orthogonal matrix.
	// A comlumns a_i are replaced by Q columns q_i
	for(int i = 1; i < m; i++) {
		gsl_vector_view a_i = gsl_matrix_column(A, i);
		double R_ii = norm(&a_i.vector); //R_ii = sqrt(a_i*a_i)
		gsl_vector_scale(&a_i.vector,1/R_ii); //q_i = a_i/R_ii
		gsl_matrix_set(R, i, i, R_ii); // Set value of matrix R
		for(int j = i+1; j < m; j++) {
			gsl_vector_view a_j = gsl_matrix_column(A, j);
			double R_ij = in_prod(&a_i.vector, &a_j.vector); // R_ij = q_i*a_j
			gsl_blas_daxpy(-R_ij, &a_i.vector, &a_j.vector); // a_j = a_j - q_i*R_ij
			gsl_matrix_set(R, i, j, R_ij); // Set value of matrix R
		}
	}
}

void GS_solve(gsl_matrix* Q, gsl_matrix* R, gsl_vector* b, gsl_vector* x) {
	/* Solve QRx = b => Rx = Q^Tb */
	gsl_blas_dgemv(CblasTrans,1,Q,b,0,x); // Calculates Q^T*b
	backsub(R, x);
}
	


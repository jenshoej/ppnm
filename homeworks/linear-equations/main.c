#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<math.h>
#include"matrix.h"

int main() {
	// Check that GS_decomp works
	
	// Allocate memory for matrices
	int n = 5;
	int m = 5;
	gsl_matrix* A = gsl_matrix_alloc(n, m);
	gsl_matrix* A_copy = gsl_matrix_alloc(n, m);
	gsl_matrix* Q = gsl_matrix_alloc(n, m);
	gsl_matrix* R = gsl_matrix_alloc(m, m);
	gsl_matrix* QTQ = gsl_matrix_alloc(m, m);
	gsl_matrix* QR = gsl_matrix_alloc(n, m);
	generate_matrix(A);
	printf("Original matrix A is\n");
	print_matrix(A);
	gsl_matrix_memcpy(Q, A);

	// Call functions
	GS_decomp(A, R);
	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, A, A, 0, QTQ);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, A, R, 0, QR);

	printf("Matrix Q^TQ should be the identity matrix\n");
	print_matrix(QTQ);
	printf("Matrix QR is, and should be equal to A\n");
	print_matrix(QR);


	gsl_matrix_free(A);
	gsl_matrix_free(Q);
	gsl_matrix_free(R);
	gsl_matrix_free(QTQ);
	gsl_matrix_free(QR);
	gsl_matrix_free(A_copy);

	return 0;
}





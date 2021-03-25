#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<math.h>
#include"matrix.h"

int part_1() {

	// Check that GS_decomp works
	printf("Checking that GS_decomp works\n");
	
	// Allocate memory for matrices
	int n = 7;
	int m = 5;

	gsl_matrix* A = gsl_matrix_alloc(n, m);
	gsl_matrix* A_copy = gsl_matrix_alloc(n, m);
	gsl_matrix* Q = gsl_matrix_alloc(n, m);
	gsl_matrix* R = gsl_matrix_alloc(m, m);
	gsl_matrix* QTQ = gsl_matrix_alloc(m, m);
	gsl_matrix* QR = gsl_matrix_alloc(n, m);

	generate_matrix(A);

	printf("Matrix A is:\n");
	
	print_matrix(A);
	gsl_matrix_memcpy(Q, A);

	// Call functions
	GS_decomp(A, R);

	printf("Matrix Q is:\n");
	print_matrix(A);

	printf("Matrix R is:\n");
	print_matrix(R);

	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, A, A, 0, QTQ);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, A, R, 0, QR);

	printf("Matrix QTQ is:\n");
	print_matrix(QTQ);

	printf("Matrix QR is:\n");
	print_matrix(QR);

	gsl_matrix_free(A);
	gsl_matrix_free(Q);
	gsl_matrix_free(R);
	gsl_matrix_free(QTQ);
	gsl_matrix_free(QR);
	gsl_matrix_free(A_copy);

	return 0;
}

void part_2() {

	// Check that GS_solve works
	printf("Checking that GS_solve works\n");

	int n = 6;
	int m = 6;

	gsl_matrix *A = gsl_matrix_alloc(n,n);
	gsl_matrix *Q = gsl_matrix_alloc(n,n);
	gsl_matrix *R = gsl_matrix_alloc(n,n);
	gsl_matrix *QR = gsl_matrix_alloc(n,n);
	gsl_vector *b = gsl_vector_alloc(n);
	gsl_vector *x = gsl_vector_alloc(n);

	generate_matrix(A);
	generate_vector(b);

	GS_decomp(A, R);
	GS_solve(
}

int main() {

	part_1();
	part_2();	
	return 0;
}

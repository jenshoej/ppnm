#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include<math.h>
#include"matrix.h"
#include<time.h>

void part_1() {

	// Check that GS_decomp works
	printf("Checking that GS_decomp works\n");
	printf("\n");

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

}

void part_2() {

	// Check that GS_solve works
	printf("Checking that GS_solve works\n");
	printf("\n");

	int n = 6;
	int m = 6;

	gsl_matrix *A = gsl_matrix_alloc(n,n);
	gsl_matrix *Q = gsl_matrix_alloc(n,n);
	gsl_matrix *R = gsl_matrix_alloc(n,n);
	gsl_matrix *QR = gsl_matrix_alloc(n,n);
	gsl_matrix *B = gsl_matrix_alloc(n,n);
	gsl_matrix *AB = gsl_matrix_alloc(n,n);
	gsl_vector *b = gsl_vector_alloc(n);
	gsl_vector *x = gsl_vector_alloc(n);
	gsl_vector *y = gsl_vector_alloc(n);

	generate_matrix(A);

	generate_vector(b);
	printf("Vector b is:\n");
	print_vector(b);
	gsl_matrix_memcpy(Q, A);

	GS_decomp(Q, R);
	GS_solve(Q, R, b, x);
	
	gsl_blas_dgemv(CblasNoTrans, 1, A, x, 0, y);

	printf("Product A*x is:\n");
	print_vector(y);

	inverse(Q, R, B);
	printf("Checking that inverse works\n");
	printf("\n");
	printf("Inverse of A is\n");
	print_matrix(B);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, A, B, 0, AB);
	printf("A*B is (should be identity\n");
	print_matrix(AB);

	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(AB);
    gsl_matrix_free(R);
    gsl_matrix_free(Q);
    gsl_vector_free(b);
    gsl_vector_free(x);
    gsl_vector_free(y);
}

void part_3() {
		int N = 7;
	    for(int i = 0; i < N; i++) {
        	gsl_matrix* M1 = gsl_matrix_alloc(N, N);
			gsl_matrix* M2 = gsl_matrix_alloc(N, N);
			generate_matrix(M1);
			generate_matrix(M2);
        	gsl_matrix* R_mat = gsl_matrix_alloc(N, N);
			gsl_matrix_set_identity(R_mat);
        	gsl_vector* tau = gsl_vector_alloc(N);
			gsl_vector_set_zero(tau);
        	clock_t start1, end1, start2, end2;
        	double time_my_QR, time_gsl;

        	// Time our own algorithm
        	start1 = clock();
        	GS_decomp(M1, R_mat);
        	end1 = clock();
        	time_my_QR = ((double)(end1 - start1))/CLOCKS_PER_SEC;

        	// Time GSL's QR decomp
        	start2 = clock();
        	gsl_linalg_QR_decomp(M2, tau);
        	end2 = clock();
        	time_gsl = ((double)(end2 - start2))/CLOCKS_PER_SEC;
        	printf("Decomposition nr.: %i\n My QR routine: %10g seconds\n GSL routine  : %10g seconds\n", i+1, time_my_QR, time_gsl);
        	gsl_matrix_free(M1);
        	gsl_matrix_free(R_mat);
        	gsl_matrix_free(M2);
        	gsl_vector_free(tau);
    }
}

int main() {


	part_1();
	part_2();	
	printf("\nPART C - TIME ELAPSED\n\n");
	part_3();
	return 0;
}

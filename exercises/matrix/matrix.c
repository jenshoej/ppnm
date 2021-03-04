#include<stdio.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<gsl/gsl_linalg.h>


void printvector(gsl_vector* v) {
	for(int i = 0; i < v->size; i++) {
		printf("%10g", gsl_vector_get(v,i));
		printf("\n");
	}
}
void printmatrix(gsl_matrix* m) {
	for(int i = 0; i < m->size1; i++){
		for(int j = 0; j < m->size2; j++) {
			printf("%10g",gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
}

int main() {
	/* Data for the exercise */
	double a_data[] = {
        6.13, -2.90, 5.86,
        8.08, -6.31, -3.89,
        -4.36, 1.00, 0.19
	};
	double b_data[] = {6.23, 5.37, 2.29};

	/* Initialize matrix */
	int n=3;
	gsl_matrix* A=gsl_matrix_alloc(n,n);
	gsl_matrix* A_copy=gsl_matrix_alloc(n,n);
	gsl_vector* b=gsl_vector_alloc(n);
	gsl_vector* x=gsl_vector_alloc(n);
	gsl_vector* y=gsl_vector_calloc(n);
	/* (i,j)'th matrix element is the (i*n + j)'th element in array*/
	for(int i = 0; i< A->size1; i++) {
		for(int j=0; j<A->size2; j++) {
			gsl_matrix_set(A,i,j,a_data[i*n + j]);
		}
	}
	gsl_matrix_memcpy(A_copy,A); //make a copy of A, since it's destroyed later
	for(int i = 0; i < b->size; i++) {
		gsl_vector_set(b,i,b_data[i]);
	}

	/* Print matrix A and vector b*/
	printf("Matrix A \n");
	printmatrix(A);
	printf("Vector b \n");
	printvector(b);

	/* solve A*x = b */
	gsl_linalg_HH_solve(A, b, x);
	
	/* print solution */
	printf("Solution to A*x = b is\n");
	printvector(x);

	/* check b is equal to A_copy*x */
	gsl_blas_dgemv(CblasNoTrans,1,A_copy,x,0,y);
	printf("Checking the solution is correct\n");
	printvector(y);
return 0;	
}

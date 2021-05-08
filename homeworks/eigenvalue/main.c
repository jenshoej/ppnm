#include <stdio.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>


void jacobi_diag(gsl_matrix* A, gsl_matrix* V);

void print_matrix(gsl_matrix* m) {
	for(int i = 0; i < m->size1; i++){
		for(int j = 0; j < m->size2; j++) {
			printf("%10.4f",gsl_matrix_get(m,i,j));
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
    int n = 7;
    int m = 7;
    gsl_matrix* A = gsl_matrix_alloc(n, m);
    gsl_matrix* A_copy = gsl_matrix_alloc(n, m);
    gsl_matrix* V = gsl_matrix_alloc(n, m);
    gsl_matrix* VtV = gsl_matrix_alloc(n, m);
    gsl_matrix* test = gsl_matrix_alloc(n, m);
    gsl_matrix* VtAV = gsl_matrix_alloc(n, m);
    gsl_matrix* VDVt = gsl_matrix_alloc(n, m);
    
    // Generate the matrix A
    for(int i = 0; i<A->size1; i++) {
	    for(int j = 0; j<A->size2; j++) {
            double random = 100*(double)rand()/RAND_MAX;
		    gsl_matrix_set(A,i,j, random);
            gsl_matrix_set(A,j,i, random);
		}
	}
    gsl_matrix_memcpy(A_copy, A);

    printf("Our matrix A is\n");
    print_matrix(A);

    jacobi_diag(A, V); // Diagonalize

    printf("Checking that V*Vt is the identity\n");
    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, V, V, 0, VtV);
    print_matrix(VtV);

    printf("Matrix D is\n");
    print_matrix(A);

    printf("Checking that Vt*A*V equals D\n");
    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, V, A_copy, 0, test);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, test, V, 0, VtAV);
    print_matrix(VtAV);

    printf("Checking that V*D*Vt equals A\n");
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, V, A, 0, test);
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1, test, V, 0, VDVt);
    print_matrix(VDVt);

    return 0;
}











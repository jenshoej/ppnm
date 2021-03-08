#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_pi(void* arg) {
	double* pi = (double*)arg;

	/* generate random numbers for x and y between 0 and 1 */
	int N = 1e8; // Number of iterations
	double N_in = 0; // Number of points inside circle
	unsigned int seed;
	for(int i = 0; i < N; i++) {
		double x = (double)rand_r(&seed)/RAND_MAX;		
		double y = (double)rand_r(&seed)/RAND_MAX;

		/* count if the length of distance from x to y is larger than 1 */
		if( sqrt(pow(x,2) + pow(y,2)) < 1) {
			N_in++;
		}	
	}
	/* calculate the ratio of pi */
	*pi = 4*N_in/N; 
	return NULL;
}

int main() {
	double pi_1, pi_2, pi_3;

	/* create threads and run calculate pi method in 3 separate threads. One runs on main thread. */
	pthread_t thread_1, thread_2;
	pthread_create(&thread_1, NULL, calculate_pi, (void*)&pi_1);
	pthread_create(&thread_2, NULL, calculate_pi, (void*)&pi_2);
	calculate_pi((void*)&pi_3);

	/* join threads */
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	/* calculate pi value average of the three threads and prints it */
	double avg = (pi_1 + pi_2 + pi_3)/3;
	printf("Value of pi = %g\n", avg);


return 0;
}


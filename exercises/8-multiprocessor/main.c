#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_pi(void* arg) {

	/* initialize variables */
	int N = 1e3; // Number of iterations
	double* pi = (double*)arg;
	double N_in = 0; // Number of points inside circle
	unsigned int seed;

	/* create files for storing datapoints for plotting */
	FILE* inside_points = fopen("inside_points.txt", "w");
	FILE* outside_points = fopen("outside_points.txt", "w");

	/* generate random numbers */
	for(int i = 0; i < N; i++) {
		double x = (double)rand_r(&seed)/RAND_MAX;		
		double y = (double)rand_r(&seed)/RAND_MAX;

		/* count if the length of distance from origin to (x,y) is larger than 1 */
		if(sqrt(x*x + y*y) < 1) {
			N_in++;
			if(x < 1) {
				fprintf(inside_points,"%g %g\n", x, y); // Add point to file with points inside of circle
			}
		}	
		else if(x < 1) {
			fprintf(outside_points,"%g %g\n", x, y); //Add point to file with points outside of circle
		}
	
	}	
	fclose(inside_points);
	fclose(outside_points);
	
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


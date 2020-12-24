#define _POSIX_C_SOURCE 199506L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "LoadBalancer.h"

// Forward declarations for internal (private) functions.
void* simulate_user_request(void* user_id);

// Variable to store load balancer object
balancer* lb;

/**
 * Entry point to simulation.
 * 
 * @return Zero.
 */
int main() {

	int number_of_requests = 10;
    	int batch_size = 5;

	printf("Please input number of requests (users): ");
	//scanf("%d", &number_of_requests);

	printf("Please input batch size: ");
	//scanf("%d", &batch_size);

	pthread_t threads[number_of_requests];

    	lb = balancer_create(batch_size);

    	// Create number_of_requests number of users that want to square a number.
    	for (int i = 0; i < number_of_requests; i++) {

        	printf("creating: %d\n", i);
        	pthread_create(&threads[i], NULL, &simulate_user_request, (void*)i);

    	}

    	nanosleep((struct timespec[]){{2, 0}}, NULL); // Wait two seconds

    	balancer_destroy(&lb);

    	// Wait for all users to finish before program exit.
    	for (int i = 0; i < number_of_requests; i++) {

        	pthread_join(threads[i], NULL);   
    
	}

    return 0;

}

/**
 * Simulates a user requesting work to be done a server. Expected to be run in a
 * thread.
 * 
 * @param user_id
 * @return 
 */
void* simulate_user_request(void* user_id) {

    int data = rand() % 100;
    int* result = (int*)malloc(sizeof(int));
    *result = -1;
    
    // Make the thread wait to simulate differences in when user requests occur.
    int ms = (rand() % 100) * 1000;
    nanosleep((struct timespec[]){{0, ms*1000000}}, NULL);
    
    printf("User #%d: Wants to process data=%d and store it at %p.\n", (int)user_id, data, result);
    
    // Make request to balance to complete job and wait for it's completion.
    balancer_add_job(lb, (int)user_id, data, result);
    while(*result == -1);  //busy waiting, bad but simple
    
    printf("User #%d: Received result from data=%d as result=%d.\n", (int)user_id, data, *result);
    
    free(result);
    
    pthread_exit(NULL);

}
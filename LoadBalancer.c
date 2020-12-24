#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "LoadBalancer.h"
#include "InstanceHost.h"

/**
* Load Balancer
* @author Noah O'Brien
* @version 1.0
*/

struct balancer {

	struct host *host;
	struct job_node *node;
	pthread_mutex_t *locker;
	int requests;
	int size;

};

balancer *balancer_create(int batch_size) {

	balancer *temp = (balancer*)malloc(sizeof(balancer));
	temp->node = (struct job_node*)malloc(sizeof(struct job_node)*batch_size);

	pthread_mutex_init(temp->locker, NULL);
	temp->requests = batch_size;
	temp->requests = 0;
	temp->host = host_create();

	return temp;

}

void balancer_destroy(balancer **lb) {

	free(*lb);
	*lb = NULL;

}

void balancer_add_job(balancer* lb, int user_id, int data, int* data_return) {

	pthread_mutex_lock(lb->locker);
	printf("LoadBalancer : New job received from user#%d for %d to store at %p. \n", user_id, data, data_return);
	lb->requests++;

	struct job_node *temp = (struct job_node*) malloc(sizeof(struct job_node));
	temp->data = data;
	temp->data_result = data_return;
	temp->next = lb->node;
	lb->node = temp;

	if(lb->requests == lb->size) {

		host_request_instance(lb->host, lb->node);

	}

	pthread_mutex_unlock(lb->locker);


}

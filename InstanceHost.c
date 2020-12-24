#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "InstanceHost.h"

/**
* Instance host
* @author Noah O'Brien
* @version 1.0
*/

struct host {

	int instances;
	pthread_t *t;

};

host *host_create() {

	pthread_t* create_instance(host* h);
	void add_instance(host* h);
	host* x = (struct host*)malloc(sizeof(host));

	x->instances = 0;
	x->t = create_instance(x);

	return x;

}

void host_destroy(host **h) {

	free(*h);
	*h = NULL;

}

void host_request_instance(host *h, struct job_node *batch) {

	void add_instance(host* h);
	void *runner(void* args) {

	pthread_exit(NULL);

	}
	pthread_create(&h->t[h->instances], NULL, runner, (void*) batch);

}


pthread_t* create_instance(host *h) {

	return (pthread_t*)malloc(sizeof(pthread_t));

}

void add_instance(host *h) {

	h->instances++;

	pthread_t* x = h->t;

	h->t = (pthread_t*)realloc(x, sizeof(pthread_t)*h->instances);

	free(x);

}

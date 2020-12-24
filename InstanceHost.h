#ifndef INSTANCEHOST_H
#define INSTANCEHOST_H

#include "LoadBalancer.h"

// Struct for representing the host
typedef struct host host;

struct job_node; //defined in LoadBalancer

// Forward declarations for (public) functions

/**
* Initializes the host environment.
*/
host* host_create();

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_destroy(host**);

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host* h, struct job_node* batch);

#endif

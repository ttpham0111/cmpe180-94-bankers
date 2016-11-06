#include <stdlib.h>
#include <pthread.h>
#include <iostream>

#include "./bank.h"

#define NUM_CUSTOMERS 8

void* request_resources(void* context);
void* release_resources(void* context);
int* get_random_resources(int num_resources);

struct thread_context {
  int customer_id;
  int num_resources;
  Bank* bank;
};

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " r1 [r2 ...]" << std::endl;
    std::cout << "\tr1, r2, etc...: # of instances of each resource.";
    std::cout << std::endl;
  }

  // Create array of resources.
  int num_resources = argc - 1;
  int* resources = new int[num_resources];

  char** p_argv = argv + 1;
  for (int r = 0; r < num_resources; ++r) {
    // atoi has undefined behaviour for non-int values.
    resources[r] = atoi(p_argv[r]);
  }

  std::cout << "Inilializing bank..." << std::endl;
  Bank* bank = new Bank(num_resources, resources, NUM_CUSTOMERS);

  std::cout << "Inilializing thread context..." << std::endl;
  thread_context** tcs = new thread_context*[NUM_CUSTOMERS];
  for (int customer_id = 0; customer_id < NUM_CUSTOMERS; ++customer_id) {
    tcs[customer_id] = new thread_context();
    tcs[customer_id]->customer_id = customer_id;
    tcs[customer_id]->num_resources = num_resources;
    tcs[customer_id]->bank = bank;
  }

  std::cout << "Starting request/release cycle..." << std::endl << std::endl;
  pthread_t customer_threads[NUM_CUSTOMERS];
  char key;
  while (key != 'q') {

    // Request resource.
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
      pthread_create(&customer_threads[i], NULL,
                     &request_resources, reinterpret_cast<void*>(tcs[i]));
    }

    // Wait for threads to finish.
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
      pthread_join(customer_threads[i], NULL);
    }

    // Release resource.
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
      pthread_create(&customer_threads[i], NULL,
                     &release_resources, reinterpret_cast<void*>(tcs[i]));
    }

    // Wait for threads to finish.
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
      pthread_join(customer_threads[i], NULL);
    }

    std::cout << "Enter any key to continue or [q] to quit..." << std::endl;
    std::cin >> key;
  }

  std::cout << "Cleaning up..." << std::endl;
  for (int customer_id = 0; customer_id < NUM_CUSTOMERS; ++customer_id) {
    delete tcs[customer_id];
  }
  delete[] resources;
  delete[] tcs;

  return 0;
}


// Requests random number of resources from the bank.
void* request_resources(void* context) {
  thread_context* tc = reinterpret_cast<thread_context*>(context);
  int *resources = get_random_resources(tc->num_resources);
  tc->bank->request_resources(tc->customer_id, tc->num_resources, resources);
  delete[] resources;
}

// Releases random number of resources to the bank.
void* release_resources(void* context) {
  thread_context* tc = reinterpret_cast<thread_context*>(context);
  int *resources = get_random_resources(tc->num_resources);
  tc->bank->release_resources(tc->customer_id, tc->num_resources, resources);
  delete[] resources;
}


int* get_random_resources(int num_resources) {
  int* resources = new int[num_resources];
  for (int i = 0; i < num_resources; ++i) {
    resources[i] = rand() % 6;
  }
  return resources;
}

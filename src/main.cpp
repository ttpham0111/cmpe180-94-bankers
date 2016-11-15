#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "./bank.h"

#define NUM_CUSTOMERS 8

void* customer(void* context);
void randomize_array(int arr[], int size, int max);
std::string to_string(int arr[], int size);

struct thread_context {
  int customer_id;
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
    tcs[customer_id]->bank = bank;
  }

  std::cout << "Starting request/release cycle..." << std::endl << std::endl;
  pthread_t customer_threads[NUM_CUSTOMERS];
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    pthread_create(&customer_threads[i], NULL,
                   &customer, reinterpret_cast<void*>(tcs[i]));
  }

  // Wait for threads to finish.
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    pthread_join(customer_threads[i], NULL);
  }

  std::cout << "Cleaning up..." << std::endl;
  for (int customer_id = 0; customer_id < NUM_CUSTOMERS; ++customer_id) {
    delete tcs[customer_id];
  }
  delete[] resources;
  delete[] tcs;

  return 0;
}

/**
 * Represents a customer that continously requests and releases
 * random number of resources from the bank.
 */
void* customer(void* context) {
  thread_context* tc = reinterpret_cast<thread_context*>(context);
  int num_resources = tc->bank->num_resources();
  int *resources = new int[num_resources];

  try {
    while (true) {

      // Request resources...
      randomize_array(resources, num_resources, 5);
      std::cout << "Customer " << tc->customer_id << " requesting " << to_string(resources, num_resources) << std::endl;
      tc->bank->request_resources(tc->customer_id, resources);

      // Delay...
      std::this_thread::sleep_for(std::chrono::seconds(1));

      // Release resources...
      randomize_array(resources, num_resources, 5);
      std::cout << "Customer " << tc->customer_id << " releasing " << to_string(resources, num_resources) << std::endl;
      tc->bank->release_resources(tc->customer_id, resources);
    }
  } catch (...) { /* do nothing */ }

  delete[] resources;
}

/**
 * Randomizes the contents of an array to values of 0-max inclusive.
 */
void randomize_array(int arr[], int size, int max) {
  for (int i = 0; i < size; ++i) {
    arr[i] = rand() % (max + 1);
  }
}

/**
 * Converts an array to a string.
 */
std::string to_string(int arr[], int size) {
  std::stringstream ss;
  std::string delimeter = "";

  ss << "[ ";
  for (int i = 0; i < size; ++i) {
    ss << delimeter << arr[i];
    delimeter = ", ";
  }
  ss << " ]";

  return ss.str();
}
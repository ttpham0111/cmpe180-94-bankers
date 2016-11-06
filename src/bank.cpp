#include <iostream>
#include "./bank.h"

Bank::Bank(int num_resources, int resources[], int num_customers)
: _num_customers(num_customers), _num_resources(num_resources) {
  //
}

Bank::~Bank() {
  //
}

int Bank::request_resources(int customer_id, int num_resources, int resources[]) {
  return 0;
}

int Bank::release_resources(int customer_id, int num_resources, int resources[]) {
  return 0;
}

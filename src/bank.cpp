#include <iostream>
#include "./bank.h"

Bank::Bank(int num_resources, int resources[], int num_customers)
: _num_customers(num_customers), _num_resources(num_resources) {
  //
}

Bank::~Bank() {
  //
}

int Bank::num_resources() {
	return _num_resources;
}

int Bank::request_resources(int customer_id, int resources[]) {
  for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
	{
		if (request[i] > need[customer_id][i])
		{
			/// raise error
			exit(1);
		}
	}

	for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
	{
		if (request[i] > available[i])
		{
			////wait for the request
		}
	}

	for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
	{
		available[i] -= request[i];
		allocation[customer_id][i] += request[i];
		need[customer_id][i] -= request[i];
	}

	bool isSafe = true;
	if (isSafe)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
		{
			available[i] += request[i];
			allocation[customer_id][i] -= request[i];
			need[customer_id][i] += request[i];
		}

		return -1;
	}
}

int Bank::release_resources(int customer_id, int resources[]) {
  return 0;
}
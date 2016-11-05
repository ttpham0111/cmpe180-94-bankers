#ifndef BANK_H
#define BANK_H

class Bank {
 public:
  Bank(int num_resources, int resources[], int num_customers);
  ~Bank();

  int request_resources(int customer_id, int resources[]);
  int release_resources(int customer_id, int resources[]);

 private:
  int _num_customers;
  int _num_resources;
  int* _available;
  int** _maximum;
  int** _allocated;
  int** _need;
};

#endif
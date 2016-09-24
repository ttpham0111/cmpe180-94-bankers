# Banker's Algorithm

## Data Structures
```
int* Available  // A vector of length *m* indicating the number of resources available for each type.
                // If Available[j] equals *k*, then *k* is the available number of resource of the type *j*
                
int** Max       // A *n* x *m* matrix defining the maximum number of resource that a process may need.
                // If Max[*i*][*j*] equals *k*, the process *i* may request up to *k* instances of resource *j*.
                
int** Allocation  // A *n* x *m* matrix defining the allocated resources for a process.
                  // If Allocation[*i*][*j*] equals *k*
```

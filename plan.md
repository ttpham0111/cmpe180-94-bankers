# Banker's Algorithm

## Data Structures
```
int* Available    // A vector of length m indicating the number of resources available for each type.
                  // If Available[j] equals k, then k is the available number of resource of the type j
                
int** Max         // A n by m matrix defining the maximum number of resource that a process may need.
                  // If Max[i][j] equals k, the process i may request up to k instances of resource j.
                
int** Allocation  // A n by m matrix defining the allocated resources for a process.
                  // If Allocation[i][j] equals k, the process i has already been allocated k instances of resource j.
                  
int** Need        // A n by m matrix defining the remaining resource needs of a process.
                  // If Need[i][j] equals k, the process i may need k more instances of resource j.
                  // Max = Allocation + Need
```

## Algorithms
These are tentative signatures for methods that we will need for the Banker's Algorithm.
```
bool is_safe()  // Checks whether or not the system is in a safe state.

void request_resource(p_id, resource_type, num_instances)  // Process a request for a resource by a process.
                                                           // Compares the amount requested by the process to
                                                           // Need, Available, and set the allocation. If the system
                                                           // is still safe after the transaction, commit else restore.
```


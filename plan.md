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
int release resources(int customer num, int release[]);

## Project Specifications
### The Banker
The banker will consider requests from n customers for m resources types. The banker will keep track of the resources using the following data structures:
```
/* these may be any values >= 0 */
#define NUMBER OF CUSTOMERS 5
#define NUMBER OF RESOURCES 3

/* the available amount of each resource */
int available[NUMBER OF RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];

/* the remaining need of each customer */
int need[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];
```
### The Customers
Create n customer threads that request and release resources from the bank. The customers will continually loop, requesting and then releasing random numbers of resources. The customers’ requests for resources will be bounded
by their respective values in the need array. The banker will grant a request only if it leaves the system in a safe state.

Function prototypes for requesting and releasing resources are as follows:
```
int request resources(int customer num, int request[]);
int release resources(int customer num, int release[]);
```
These two functions should return 0 if successful (the request has been granted) and –1 if unsuccessful. Multiple threads (customers) will concurrently access shared data through these two functions. Therefore, access must be controlled through mutex locks to prevent race conditions.

The program should be invoked by passing the number of resources of each type on the command line. For example, if there were three resource types, with ten instances of the first type, five of the second type, and seven of the third type, the command to invoke the program should be:
```
./a.out 10 5 7
```
The available array would be initialized to these values. The maximum array may be initialized using any method.

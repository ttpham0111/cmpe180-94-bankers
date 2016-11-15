/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
/* the available amount of each resource */
int available[NUMBER OF RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];
/* the remaining need of each customer */
int need[NUMBER OF CUSTOMERS][NUMBER OF RESOURCES];

int main ()
{
	
	
	return 0;
}

int release_resources(int customer_id, int request[])
{
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



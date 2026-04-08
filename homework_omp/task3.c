#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <float.h>

#define N 50000000

int main()
{
	double *arr = malloc(N*sizeof(double));
	if(arr==NULL)
	{
		printf("Malloc didn''t malloc :(\n");
		return 1;
	}
	for(int i=0;i<N;i++)
	{
		arr[i]=rand()/(double)RAND_MAX;
	}
	double max = -DBL_MAX;

	#pragma omp parallel for reduction(max:max)
	for(int i=0;i<N;i++)
	{
		if(arr[i]>max)
		{
			max=arr[i];
		}
	}

	double t=0.8*max;
	double sum=0;

	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<N;i++)
	{
		if(arr[i]>t)
		{
			sum+=arr[i];
		}
	}

	printf("The sum of elements is: %.10f\n", sum);
	free(arr);
	return 0;
}

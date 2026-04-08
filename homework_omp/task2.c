#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <float.h>
#include <math.h>

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
	double min = DBL_MAX;

	#pragma omp parallel for reduction(min:min)
	for(int i=0;i<N-1;i++)
	{
		double d=fabs(arr[i]-arr[i+1]);
		if(d<min)
		{
			min=d;
		}
	}

	printf("The minimum distance is: %.10f\n", min);
	free(arr);
	return 0;
}

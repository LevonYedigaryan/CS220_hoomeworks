#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define RANGE 256

int main()
{
	int *arr = malloc(N*sizeof(int));
	if(arr==NULL)
	{
		printf("Malloc didn't malloc :(\n");
		return 1;
	}
	int hist[RANGE];
	for(int i=0;i<N;i++)
	{
		arr[i]=rand()%RANGE;
	}
	for(int i=0;i<RANGE;i++)
	{
		hist[i]=0;
	}

	#pragma omp parallel for
	for(int i=0;i<N;i++)
	{
		hist[arr[i]]++;
	}

	printf("Results for the naive version are:\n");
	for(int i=0;i<RANGE;i++)
	{
		printf("%d occured %d times", i, hist[i]);
		if(i+1!=RANGE)
		{
			printf(",");
		}
		printf("\n");
	}
	for(int i=0;i<RANGE;i++)
	{
		hist[i]=0;
	}

	#pragma omp parallel for
	for(int i=0;i<N;i++)
	{
		#pragma omp critical
		{
			hist[arr[i]]++;
		}
	}

	printf("Results for the critical version are:\n");
	for(int i=0;i<RANGE;i++)
        {
                printf("%d occured %d times", i, hist[i]);
                if(i+1!=RANGE)
                {
                        printf(",");
                }
                printf("\n");
        }
	for(int i=0;i<RANGE;i++)
	{
		hist[i]=0;
	}

	#pragma omp parallel for reduction(+:hist[:RANGE])
	for(int i=0;i<N;i++)
	{
		hist[arr[i]]++;
	}

	printf("Results for the reduction version are:\n");
	for(int i=0;i<RANGE;i++)
        {
                printf("%d occured %d times", i, hist[i]);
                if(i+1!=RANGE)
                {
                        printf(",");
                }
                printf("\n");
	}
	free(arr);
	return 0;
}

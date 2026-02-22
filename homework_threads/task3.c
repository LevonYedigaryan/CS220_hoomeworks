#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

struct Bounds
{
	int start;
	int end;
	int *arr;
	int res;
};

void* maximizer(void* args)
{
	struct Bounds bounds = *((struct Bounds*) args);
	int s=bounds.start;
	int e=bounds.end;
	int max=INT_MIN;
	for(int i=s;i<e;i++)
	{
		if(bounds.arr[i]>max)
		{
			max=bounds.arr[i];
		}
	}
	struct Bounds* b = (struct Bounds*) args;
	b->res=max;
	return NULL;
}

int main()
{
	int n;
	printf("Please input the length of the array: ");
	scanf("%d", &n);
	int *a = malloc(n*sizeof(int));
	if(a==NULL)
	{
		printf("Couldn't create the array :(\n");
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		a[i]=i;
	}
	int max=INT_MIN;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<n;i++)
	{
		if(a[i]>max)
		{
			max=a[i];
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
	printf("The maximum number is %d: Calculated sequentially in %.6f seconds.\n", max, t);
	pthread_t threads[4];
	int s=0, e=n/4;
	struct Bounds bounds[4];
	max=INT_MIN;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<4;i++)
	{
		bounds[i].start=s;
		bounds[i].end=e;
		bounds[i].arr=a;
		if(pthread_create(&threads[i], NULL, maximizer, &bounds[i])!=0)
		{
			perror("Couldn't create th threads :(\n");
			return 1;
		}
		s=e;
		e+=n/4;
		if(i+2>=4)
		{
			e=n;
		}
	}
	for(int i=0;i<4;i++)
	{
		pthread_join(threads[i], NULL);
	}
	for(int i=0;i<4;i++)
	{
		if(bounds[i].res>max)
		{
			max=bounds[i].res;
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
        printf("The maximum number is %d: Calculated with threads in %.6f seconds.\n", max, t);
	free(a);
	return 0;
}

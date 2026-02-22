#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

const int N=20000000;

struct Bounds
{
	int start;
	int end;
	int count;
};

void* primeCounter(void* args)
{
	struct Bounds bounds = *((struct Bounds*) args);
	int s=bounds.start;
	int e=bounds.end;
	int count=0;
	for(int i=s;i<e;i++)
	{
		int t=2;
		while(i%t!=0 && t<sqrt(i))
		{
			t++;
		}
		if(t>sqrt(i) && i>1)
		{
			count++;
		}
	}
	struct Bounds* b = (struct Bounds*) args;
	b->count=count;
	return NULL;
}

int main()
{
	int count=0;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<N;i++)
	{
		int t=2;
                while(i%t!=0 && t<sqrt(i))
                {
                        t++;
                }
                if(t>sqrt(i) && i>1)
                {
                        count++;
                }
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
	printf("The number of prime numbers is %d: Calculated sequentially in %.6f seconds.\n", count, t);
	pthread_t threads[10];
	int s=0, e=N/10;
	count=0;
	struct Bounds bounds[10];
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<10;i++)
	{
		bounds[i].start=s;
		bounds[i].end=e;
		if(pthread_create(&threads[i], NULL, primeCounter, &bounds[i])!=0)
		{
			perror("Couldn't create th threads :(\n");
			return 1;
		}
		s=e;
		e+=N/10;
	}
	for(int i=0;i<10;i++)
	{
		pthread_join(threads[i], NULL);
		count+=bounds[i].count;
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
        printf("The number of prime numbers is %d: Calculated with threads in %.6f seconds.\n", count, t);
	return 0;
}

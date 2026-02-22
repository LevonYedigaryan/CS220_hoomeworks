#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>

const int M=50000000;

void* work(void* args)
{
	for(int i=0;i<M;i++)
	{
		//nothing to look here
	}
	printf("Thread %ld is running in the CPU %d.\n", pthread_self(), sched_getcpu());
}

int main()
{
	int n;
	printf("Please, input the number of threads: ");
	scanf("%d", &n);
	pthread_t *threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL)
	{
		printf("Malloc failed :(\n");
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		if(pthread_create(&threads[i], NULL, work, NULL)!=0)
		{
			perror("Couldn't create the thread :(\n");
			return 1;
		}
	}
	for(int i=0;i<n;i++)
	{
		pthread_join(threads[i], NULL);
	}
	free(threads);
	return 0;
}

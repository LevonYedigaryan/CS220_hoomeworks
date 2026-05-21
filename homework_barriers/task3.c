#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int s;
int* values;
pthread_barrier_t barrier;

void* stations(void* arg)
{
	int id = *(int*)arg;
	int temp=rand()%61-30;
	values[id]=temp;
	printf("Station %d recorded %d degrees\n", id, temp);
	pthread_barrier_wait(&barrier);
	if(id==0)
	{
		int sum=0;
		for(int i=0;i<s;i++)
		{
			sum+=values[i];
		}
		printf("The average temperature today was %.2f degrees\n", sum/(float)s);
	}
        return NULL;
}

int main()
{
	printf("Please input the number of stations: ");
	scanf("%d", &s);
	values=malloc(s*sizeof(int));
	pthread_t* threads;
	threads=malloc(s*sizeof(pthread_t));
	int* indexes=malloc(s*sizeof(int));
	if(threads==NULL || indexes==NULL || values==NULL)
	{
		printf("Malloc :(\n");
		return 1;
	}
	pthread_barrier_init(&barrier, NULL, s);
	for (int i=0; i<s; i++)
	{
		indexes[i]=i;
		pthread_create(&threads[i], NULL, stations, &indexes[i]);
	}
	for (int i=0; i<s; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	free(threads);
	free(values);
	free(indexes);
	return 0;
}

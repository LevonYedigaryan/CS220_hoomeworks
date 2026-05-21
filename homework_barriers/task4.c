#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int s;
pthread_barrier_t barrier;

void* work(void* arg)
{
	int id = *(int*)arg;
	int dur=rand()%5+1;
	printf("Worker %d started working on stage 1\n", id);
	sleep(dur);
	printf("Worker %d finished working on stage 1\n", id);
	pthread_barrier_wait(&barrier);
	dur=rand()%5+1;
        printf("Worker %d started working on stage 2\n", id);
        sleep(dur);
        printf("Worker %d finished working on stage 2\n", id);
	pthread_barrier_wait(&barrier);
	dur=rand()%5+1;
        printf("Worker %d started working on stage 3\n", id);
        sleep(dur);
        printf("Worker %d finished working on stage 3\n", id);
        pthread_barrier_wait(&barrier);
        return NULL;
}

int main()
{
	printf("Please input the number of workers: ");
	scanf("%d", &s);
	pthread_t* threads;
	threads=malloc(s*sizeof(pthread_t));
	int* indexes=malloc(s*sizeof(int));
	if(threads==NULL || indexes==NULL)
	{
		printf("Malloc :(\n");
		return 1;
	}
	pthread_barrier_init(&barrier, NULL, s);
	for (int i=0; i<s; i++)
	{
		indexes[i]=i;
		pthread_create(&threads[i], NULL, work, &indexes[i]);
	}
	for (int i=0; i<s; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	free(threads);
	free(indexes);
	return 0;
}

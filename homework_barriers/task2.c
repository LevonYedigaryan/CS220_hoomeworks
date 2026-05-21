#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int p;
pthread_barrier_t barrier;

void* player(void* arg)
{
	int id = *(int*)arg;
	int sl=rand()%5+1;
	printf("Player: %d gets ready.\n", id);
	sleep(sl);
	printf("Player: %d is ready.\n", id);
	pthread_barrier_wait(&barrier);
	if(id==0)
	{
		printf("Happy hunger games, and may the odds be always in your favour!\n");
	}
        return NULL;
}

int main()
{
	printf("Please input the number of players: ");
	scanf("%d", &p);
	pthread_t* threads;
	threads=malloc(p*sizeof(pthread_t));
	int* indexes=malloc(p*sizeof(int));
	if(threads==NULL || indexes==NULL)
	{
		printf("Malloc :(\n");
		return 1;
	}
	pthread_barrier_init(&barrier, NULL, p);
	for (int i=0; i<p; i++)
	{
		indexes[i]=i;
		pthread_create(&threads[i], NULL, player, &indexes[i]);
	}
	for (int i=0; i<p; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	free(threads);
	free(indexes);
	return 0;
}

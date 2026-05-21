#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int p;
int r;
pthread_barrier_t barrier;
int* dice;
int* wins;

void* player(void* arg)
{
	int id = *(int*)arg;
	for (int i=0; i<r; i++)
	{
		dice[id] = rand() % 6 + 1;
		printf("Player %d rolled %d in round %d\n", id, dice[id], i+1);
		pthread_barrier_wait(&barrier);
		int max=0;
		int winner=-1;
		if(id==0)
		{
			for(int i=0;i<p;i++)
			{
				if(dice[i]>max)
				{
					max=dice[i];
					winner=i;
				}
			}
			wins[winner]++;
			printf("Round %d winner: Player %d\n", i+1, winner);
		}
		pthread_barrier_wait(&barrier);
	}
        return NULL;
}

int main()
{
	printf("Please input the number of players: ");
	scanf("%d", &p);
	printf("\nPlease input the number of rounds: ");
	scanf("%d", &r);
	dice=malloc(p*sizeof(int));
	wins=malloc(p*sizeof(int));
	pthread_t* threads;
	threads=malloc(p*sizeof(pthread_t));
	int* indexes=malloc(p*sizeof(int));
	if(dice==NULL || wins==NULL || threads==NULL || indexes==NULL)
	{
		printf("Malloc :(\n");
		return 1;
	}
	pthread_barrier_init(&barrier, NULL, p);
	for (int i=0; i<p; i++)
	{
		wins[i] = 0;
		indexes[i]=i;
		pthread_create(&threads[i], NULL, player, &indexes[i]);
	}
	for (int i=0; i<p; i++)
	{
		pthread_join(threads[i], NULL);
	}
	int max=0;
	int id=0;
	for (int i=0; i<p; i++)
	{
		if (wins[i]>max)
		{
			id=i;
			max=wins[i];
		}
	}
	printf("\nThe winner of the game is: Player %d with %d wins\n", id, wins[id]);
	pthread_barrier_destroy(&barrier);
	free(dice);
	free(wins);
	free(threads);
	free(indexes);
	return 0;
}

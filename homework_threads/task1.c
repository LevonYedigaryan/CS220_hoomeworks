#include <stdio.h>
#include <pthread.h>

void* print(void* args)
{
	printf("Thread %ld is running.\n", pthread_self());
	return NULL;
}

int main()
{
	pthread_t threads[3];
	for(int i=0;i<3;i++)
	{
		if(pthread_create(&threads[i], NULL, print, NULL) != 0)
		{
			perror("coudln't create the thread :(\n");
			return 1;
		}
	}
	for(int i=0;i<3;i++)
        {
		pthread_join(threads[i], NULL);
	}
	return 0;
}

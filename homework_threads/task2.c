#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

struct Bounds
{
	int start;
	int end;
	int *arr;
};

void* summarizer(void* args)
{
	struct Bounds bounds = *((struct Bounds*) args);
	int s=bounds.start;
	int e=bounds.end;
	int *res=malloc(sizeof(int));
	*res=0;
	for(int i=s;i<e;i++)
	{
		*res=*res+bounds.arr[i];
	}
	return res;
}

int main()
{
	int n, m;
	printf("Please input the length of the array: ");
	scanf("%d", &n);
	printf("Please input the number of the threads: ");
	scanf("%d", &m);
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
	int sum=0;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
	printf("The sum is %d: Calculated sequentially in %.6f seconds.\n", sum, t);
	pthread_t *threads = (pthread_t*)malloc(m*sizeof(pthread_t));
	if(threads==NULL)
	{
		printf("Couldn't create the array :(\n");
		return 1;
	}
	sum=0;
	int *part;
	int s=0, e=n/m;
	struct Bounds *bounds = malloc(m*sizeof(struct Bounds));
	if(bounds==NULL)
        {
                printf("Couldn't create the array :(\n");
                return 1;
	}
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0;i<m;i++)
	{
		bounds[i].start=s;
		bounds[i].end=e;
		bounds[i].arr=a;
		if(pthread_create(&threads[i], NULL, summarizer, &bounds[i])!=0)
		{
			perror("Couldn't create th threads :(\n");
			return 1;
		}
		s=e;
		e+=n/m;
		if(i+2>=m)
		{
			e=n;
		}
	}
	for(int i=0;i<m;i++)
	{
		pthread_join(threads[i], (void**)&part);
		sum+=*part;
		free(part);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1e9;
        printf("The sum is %d: Calculated with threads in %.6f seconds.\n", sum, t);
	free(a);
	free(threads);
	free(bounds);
	return 0;
}

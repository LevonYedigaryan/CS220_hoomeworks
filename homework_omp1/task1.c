#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef struct
{
	int request_id;
	int user_id;
	int response_time;
} Entry;

int main()
{
	int n=20000;
	Entry entries[20000];
	int types[3];
	for(int i=0;i<3;i++)
	{
		types[i]=0;
	}
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			for(int i=0;i<n;i++)
			{
				entries[i].request_id=i;
				entries[i].user_id=rand()%n;
				entries[i].response_time=rand()%1000;
			}
		}
		#pragma omp barrier
		#pragma omp for
		for(int i=0;i<n;i++)
		{
			int t=entries[i].response_time;
			if(t<100)
			{
				#pragma omp atomic
				types[0]++;
				continue;
			}
			if(t<=300)
			{
				#pragma omp atomic
                                types[1]++;
                                continue;
			}
			#pragma omp atomic
			types[2]++;
		}
		#pragma omp barrier
		#pragma omp single
		{
			printf("The number of fast responses was %d, mediums %d, and longs %d.\n", types[0], types[1], types[2]);
		}
	}
	return 0;
}

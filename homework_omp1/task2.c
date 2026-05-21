#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef struct
{
	int order_id;
	int distance_km;
	int priority;
} Order;

int main()
{
	int n=10000;
	Order orders[10000];
	int threshhold;
	int thread_high_count[4]={0};
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			threshhold=20;
		}
		#pragma omp barrier
		#pragma omp for
		for(int i=0;i<n;i++)
		{
			orders[i].order_id=i;
                        orders[i].distance_km=rand()%100;
			int t=orders[i].distance_km;
			if(t<threshhold)
			{
				orders[i].priority=100;
				continue;
			}
			orders[i].priority=0;
		}
		#pragma omp barrier
		#pragma omp single
                {
                        printf("Priority assignment is finished\n");
                }
		#pragma omp for
                for(int i=0;i<n;i++)
                {
                        if(orders[i].priority==100)
			{
				thread_high_count[omp_get_thread_num()]++;
			}
		}
		#pragma omp barrier
		#pragma omp single
		{
			printf("The numbers computed by threads are %d, %d, %d, and %d\nThe total number is %d\n", thread_high_count[0], thread_high_count[1], thread_high_count[2], thread_high_count[3], thread_high_count[1]+thread_high_count[2]+thread_high_count[3]+thread_high_count[0]);
		}
	}
	return 0;
}

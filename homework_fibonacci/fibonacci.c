#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int *arr;

int fibonacci(int n)
{
	if(n<=1)
	{
		arr[n]=n;
		return arr[n];
	}
	if(arr[n]!=-1)
	{
		return arr[n];
	}
	if(n<=10)
	{
		arr[n]=fibonacci(n-1)+fibonacci(n-2);
		return arr[n];
	}
	int a, b;
	#pragma omp task shared(a)
	{
		a=fibonacci(n-1);
	}
	#pragma omp task shared(b)
	{
		b=fibonacci(n-2);
	}
	#pragma omp taskwait
	arr[n]=a+b;
	return arr[n];
}

int main()
{
	int n;
	printf("Please, enter the length of the Fibonacci sequence: ");
	scanf("%d", &n);
	arr=malloc((n+1)*sizeof(int));
	if(arr==NULL)
	{
		printf("Malloc couldn't malloc :(\n");
		return 1;
	}
	for(int i=0;i<n+1;i++)
	{
		arr[i]=-1;
	}
	#pragma omp parallel
	{
		#pragma omp single
		{
			fibonacci(n);
		}
	}
	for(int i=0;i<n+1;i++)
	{
		printf("%d", arr[i]);
		if(i+1!=n+1)
		{
			printf(", ");
		}
		else
		{
			printf("\n");
		}
	}
	free(arr);
	return 0;
}

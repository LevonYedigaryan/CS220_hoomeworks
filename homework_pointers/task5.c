#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *kakadu = (int*)malloc(sizeof(int));
	if(kakadu==NULL)
	{
		printf("Malloc fail\n");
		return 1;
	}
	*kakadu = 32854;
	printf("The value is: %d\nThe array is: ", *kakadu);
	int *dzmeruk = (int*)malloc(5*sizeof(int));
	for(int i=0;i<5;i++)
	{
		*(dzmeruk+i) = 3254+i;
		printf("%d ", *(dzmeruk+i));
	}
	printf("\n");
	free(kakadu);
	free(dzmeruk);
	return 0;
}

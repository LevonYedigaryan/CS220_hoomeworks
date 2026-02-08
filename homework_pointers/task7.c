#include <stdio.h>
#include <stdlib.h>

int main()
{
	char **kakadu = (char**)malloc(5*sizeof(char*));
	if(kakadu==NULL)
	{
		printf("Malloc failed\n");
		return 1;
	}
	*kakadu = "dzmeruk";
	*(kakadu+1) = "xndzoreni";
	*(kakadu+2) = "blur";
	*(kakadu+3) = "Lalaland";
	*(kakadu+4) = "Llama";
	for(int i=0;i<5;i++)
	{
		printf("The string number %d is: ", i);
		printf("%s", *(kakadu+i));
		printf("\n");
	}
	free(kakadu);
	return 0;
}

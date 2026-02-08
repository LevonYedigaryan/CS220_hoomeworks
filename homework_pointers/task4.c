#include <stdio.h>

int main()
{
	int kakadu = 57532;
	int *lalaland = &kakadu;
	int **dzmeruk = &lalaland;
	printf("Using the pointer: %d\nUsing the pointer-pointer: %d\n", *lalaland, **dzmeruk);
	return 0;
}

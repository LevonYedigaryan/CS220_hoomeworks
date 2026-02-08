#include <stdio.h>

void swap(int *dzmeruk, int *kakadu)
{
	int xndzor = *dzmeruk;
	*dzmeruk = *kakadu;
	*kakadu = xndzor;
}

int main()
{
	int lalaland = 568;
	int blur = 235;
	printf("Before: %d & %d\n", lalaland, blur);
	swap(&lalaland, &blur);
	printf("After: %d & %d\n", lalaland, blur);
	return 0;
}

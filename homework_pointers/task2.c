#include <stdio.h>

int main()
{
	int kakadu[5] = {1, 2, 3, 5678, 8};
	int *kakaduPointer = kakadu;
	printf("Printing the values of the array: ");
	for(int i=0;i<5;i++)
	{
		printf("%d ", *(kakaduPointer+i));
	}
	printf("\nChanging the values\nPrinting using the pointer: ");
	for(int i=0;i<5;i++)
        {
                *(kakaduPointer+i) += i;
		printf("%d ", *(kakaduPointer+i));
        }
	printf("\nPrinting using the array: ");
	for(int i=0;i<5;i++)
        {
                printf("%d ", kakadu[i]);
        }
	printf("\n");
	return 0;
}

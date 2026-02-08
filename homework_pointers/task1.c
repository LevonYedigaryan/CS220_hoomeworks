#include <stdio.h>

int main()
{
	int kakadu = 56;
	int *kakaduPointer = &kakadu;
	printf("Address using the integer: %p\n", &kakadu);
	printf("Address using the pointer: %p\n", kakaduPointer);
	*kakaduPointer = 57;
	printf("Value after changes: %d\n", kakadu);
	return 0;
}

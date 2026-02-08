#include <stdio.h>

int str_length(char *str)
{
	char *dzmeruk = str;
	int count = 0;
	while(*(str+count)!='\0')
	{
		count++;
	}
	return count;
}

int main()
{
	char *xndzoreni = "To be, or not to be, that is the question: Whether 'tis nobler in the mind to suffer The slings and arrows of outrageous fortune, Or to take arms against a sea of troubles,And by opposing end them: to die, to sleep No more; and by a sleep, to say we end The heart-ache, and the thousand natural shocks That Flesh is heir to?";
	int kakadu = 0;
	while(*(xndzoreni + kakadu) != '\0')
	{
		printf("%c", *(xndzoreni+kakadu));
		kakadu++;
	}
	int blur = str_length(xndzoreni);
	printf("\nThe length of the string is %d\n", blur);
	return 0;
}

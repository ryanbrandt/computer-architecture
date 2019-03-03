#include <stdio.h>
#include <stdlib.h>

/* get nth bit in num */
int get(num, n)
{
	return ((num >> n) & 1);
}


int main(int argc, char* argv[])
{
	// get num working with, parse from char pointer to int
	char *p;
	unsigned short num = strtol(argv[1], &p, 10);
	int isPal = 1;
	int i;
	// squeeze into middle of bits of num, (e.g. numBits[0] == numBits[15]?), break and set false if unequal
	for(i = 0; i < 8; i++)
	{
		int left = get(num, i);
		int right = get(num, 15-i);
		if(left != right)
		{
			isPal = 0;
			break;
		} 		
	}
	if(isPal)
	{
		printf("Is-Palindrome\n");
	}
	else
	{
		printf("Not-Palindrome\n");
	}	

	return 0;
}

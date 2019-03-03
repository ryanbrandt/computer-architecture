#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	// parse char pointer from argv to unsigned int for use
	char *p;
	unsigned int num = strtol(argv[1], &p, 10);
	// count for parity, prevOne to check pairs, numPairs for out
	int count = 0;
	int prevOne = 0;
	int numPairs = 0;

	/* iterate over num, reading and removing last bit at every iteration */
	while(num)
	{
		// get rightmost bit and remove it from num
		int curBit = (1 << 0) & num;
		num >>= 1;
		// increment count, check for pair
		if(curBit == 1 && prevOne)
		{
			numPairs++;
			count++;
			prevOne = 0;
		}
		else if(curBit == 1)
		{
			count++;
			prevOne = 1;
		}
		else
		{
			prevOne = 0;
		}
	}
	if(count % 2 == 0)
	{
		printf("Even-Parity\t%d\n", numPairs);
	}
	else
	{
		printf("Odd-Parity\t%d\n", numPairs);
	}

	return 0; 
}

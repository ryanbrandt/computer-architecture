#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE *f;
	f = fopen(argv[1], "r");
	// get num operating on, set vars for args
	unsigned short num;
	fscanf(f, "%hu\n", &num);
	int argOne;
	int argTwo;
	char command[5];

	/* read file, do operation */
	while(fscanf(f, "%s\t%d\t%d\n", &command[0], &argOne, &argTwo) != EOF)
	{
		switch(command[0])
		{
			case 'g':
				// get nth bit of num
				printf("%d\n", (num >> argOne) & 1);
				break;
			case 'c':
				// set nth bit of num to its complement
				num ^= 1UL << argOne;	
				printf("%d\n", num);
				break;
			case 's':
				// set nth bit of num to value of second argument
				num ^= (-argTwo ^ num) & (1UL << argOne);
				printf("%d\n", num);
		}
		
	}
	fclose(f);
	return 0;
}

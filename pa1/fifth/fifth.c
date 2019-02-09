#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){

char *vowels = "aeiou";
int i;
int j;
int k;
for(i=1; i < argc; i++)
{
	for(k = 0; argv[i][k]; k++)	
	{	for(j = 0; vowels[j]; j++)
		{
			if(vowels[j] == argv[i][k])
			{
				printf("%c", vowels[j]);
				break;
			} 
	
		}
	}
}
printf("\n");
return 0;

}

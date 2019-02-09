#include <stdio.h>
#include <stdlib.h>
#define NUMBUCKETS 10000

typedef struct LLNode
{
	int data;
	struct LLNode *next;
}LLNode;

typedef struct LinkedList
{
	struct LLNode *head;
	int size;
}LinkedList;

typedef struct HashTable
{
	struct LinkedList table[NUMBUCKETS];
}HashTable;
/* positive modulus helper */
int posMod(int num)
{
	return (num % NUMBUCKETS + NUMBUCKETS) % NUMBUCKETS;
}
/* insert to hash table */
void insert(HashTable **t, int *numCollision, int num)
{
	int hash = posMod(num);
	HashTable *hashPtr = *t;
	// check if bucket empty
	if(hashPtr->table[hash].size > 0)
	{
		// check if num exists in table
		LLNode *ptr = hashPtr->table[hash].head;
		while(ptr != NULL)
		{
			if(ptr->data == num)
			{
				break;
			}
			ptr = ptr->next;
		}
		// add to front
		if(ptr == NULL)
		{
			LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
			newNode->data = num;
			newNode->next = hashPtr->table[hash].head;
			hashPtr->table[hash].head = newNode;
			hashPtr->table[hash].size++;
		}
		++*numCollision;
		
	}
	// empty bucket, make head
	else
	{
		LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
		newNode->data = num;
		hashPtr->table[hash].head = newNode;
		hashPtr->table[hash].size++;
	}
	
}
/* search hash table */
void search(HashTable **t, int *numSuccess, int num)
{
	int hash = posMod(num);
	HashTable *hashPtr = *t;
	// check if nonempty bucket, if so, search
	if(hashPtr->table[hash].size > 0)
	{
		LLNode *ptr = hashPtr->table[hash].head;
		while(ptr != NULL)
		{
			if(ptr->data == num)
			{
				++*numSuccess;
				break;
			}
			ptr = ptr->next;
		}

	}


}

int main(int argc, char *argv[])
{
	FILE *f;
	f = fopen(argv[1], "r");
	// get operation & num, do operation with num
	char operation;
	int num;
	int numSuccess = 0;
	int numCollision = 0;
	HashTable *t = (HashTable *)malloc(sizeof(HashTable));
	while(fscanf(f, "%c\t%d\n", &operation, &num) != EOF)
	{
		switch(operation)
		{

			case 'i':
				insert(&t, &numCollision, num);
				break;
			case 's':
				search(&t, &numSuccess, num);
				break;
		}

	}
	printf("%d\n%d\n", numCollision, numSuccess);


	return 0;
}

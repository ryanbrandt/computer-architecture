#include <stdio.h>
#include <stdlib.h>

struct LinkedList
{
	struct LLNode *head;
	int size;
};

struct LLNode
{
	int data;
	struct LLNode *next;

};
/* Linked list sequential insert */
void insert(struct LLNode **head, struct LinkedList *list, int data)
{
	list->size++;
	// init space and local variables
	int inserted = 0;
	struct LLNode *toInsert = (struct LLNode *)malloc(sizeof(struct LLNode));	
	toInsert->data = data;
	toInsert->next = NULL;
	struct LLNode *ptr = *head;
	struct LLNode *prev = NULL;

	// find place 
	while(ptr != NULL)
	{
		if(data <= ptr->data)
		{
			if(prev == NULL)
			{
				struct LLNode *tmp = ptr;
				*head = toInsert;
				toInsert->next = tmp;
			}
			else
			{
				prev->next = toInsert;
				toInsert->next = ptr;
			}
			inserted = 1;
			break;
		
		}	
		prev = ptr;
		ptr = ptr->next;
	}
	// if belongs at end of list
	if(inserted == 0)
	{
		prev->next = toInsert;
	}
}

void delete(struct LLNode **head, struct LinkedList *list, int num)
{
	struct LLNode *ptr = *head;
	struct LLNode *prev = NULL;
	// search for num 
	while(ptr != NULL)
	{
		if(ptr->data == num)
		{
			// removing front of list
			if(prev == NULL)
			{
		 		// check if next for NP-safety, if not just reset
				if(ptr->next != NULL)
				{
					*head = ptr->next;
				}
				else
				{
					ptr->data = 0;
				}
			}
			// removing in middle of list, free removed node space
			else
			{
				prev->next = ptr->next;
			}
			list->size--;
			break;
		}
		prev = ptr;
		ptr = ptr->next;

	}



}
int main(int argc, char *argv[])
{
	 
	FILE *f;
	f = fopen(argv[1], "r");
	if(f == NULL)
	{
		printf("error\n");
		return 0;
	}	
	// read operation and num 
	char operation;
	int num;
	struct LinkedList front;
	struct LLNode *head = (struct LLNode *)malloc(sizeof(struct LLNode));
	front.head = head;
	front.size = 0;

	while(fscanf(f, "%c\t%d\n", &operation, &num) != EOF)
	{	
		// if insert, do insert, else do delete 
		if((char) operation == 'i')
		{
			// check if list empty, if so, make cur num head
			if(front.size == 0)
			{
				head->data = num;
				head->next = NULL;
				front.size++;
			}
			else
			{
				insert(&(front.head), &front,  num);
			}
		} 
		else
		{
			if(front.size > 0)
			{
				delete(&(front.head), &front, num);
			}
		}

	
	}
	fclose(f);
	// out
	if(front.size == 0)
	{
		printf("%d\n", 0);
	}
	else
	{
		printf("%d\n", front.size);
		struct LLNode *ptr = front.head;
		int prevNum;
		while(ptr != NULL)
		{
			if(ptr->data != prevNum)
			{		
				prevNum = ptr->data;
				printf("%d\t", ptr->data);
			}
	
			ptr = ptr->next;
		}
	}
	return 0;
}

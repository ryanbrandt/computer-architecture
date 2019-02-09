#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode
{
	int data;
	struct BSTNode *leftChild;
	struct BSTNode *rightChild;
} BSTNode;

typedef struct BST
{
	int size;
	BSTNode *root;
} BST;

/* insert into BST */
void insert(BST *tree, int data)
{
	BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
	newNode->data = data;
	
	BSTNode *ptr = tree->root;
	BSTNode *prev = NULL;
	// find place
	while(ptr != NULL)
	{
		if(ptr->data > data)
		{
			prev = ptr;
			ptr = ptr->leftChild;
		}
		else
		{
			prev = ptr;
			ptr = ptr->rightChild;
		}
	}
	// insert
	if(prev != NULL)
	{
		if(prev->data > data)
		{
			prev->leftChild = newNode;
		}
		else
		{
			prev->rightChild = newNode;
		}
	}
	else
	{
		tree->root = newNode;
	}
	tree->size++;
	
}
/* out with inorder traversal, print each num only once */
void inOrder(BSTNode *root, int *prevNum, int *isInit)
{
	BSTNode *ptr = root;
	if(ptr->leftChild != NULL)
	{
		inOrder(ptr->leftChild, prevNum, isInit);	
	}
	// if we have initialized prevNum, make sure not double printing
	if(*isInit)
	{
		if(ptr->data != *prevNum)
		{
			printf("%d\t", ptr->data);
			*prevNum = ptr->data;
		}
	}
	else
	{
		printf("%d\t", ptr->data);
		*prevNum = ptr->data;
		*isInit = 1;
	}
	if(ptr->rightChild)
	{
		inOrder(ptr->rightChild, prevNum, isInit);
	}
}

int main(int argc, char* argv[])
{
	FILE *f;
	f = fopen(argv[1], "r");
	
	int curNum;
	BST *tree = (BST *)malloc(sizeof(BST));
	// insert
	while(fscanf(f, "%*c\t%d\n", &curNum) != EOF)
	{
		insert(tree, curNum);		

	}
	fclose(f);
	// out inorder
	int *prevNum = (int *)malloc(sizeof(int));
	int* isInit = (int *)malloc(sizeof(int));
	*isInit = 0;
	inOrder(tree->root, prevNum, isInit);
	printf("\n");
	
	return 0;
}

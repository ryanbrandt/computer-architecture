#include <stdio.h>
#include <stdlib.h>

/* matrix multiplication: takes matrices, result dimensions and # of cols of left matrix */
void matMult(int **matOne, int **matTwo, int **result, int m, int k, int cols)
{
	int curProduct;
	int i;
	int j;
	int p;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < k; j++)
		{
			result[i][j] = 0;
			for(p = 0; p < cols; p++)
			{
				result[i][j] += (matOne[i][p])*(matTwo[p][j]);
			}
		}
	}
}

/* allocate space in rows */
void mallocMat(int rows, int columns, int **matrix)
{
	int i;
	for(i = 0; i < rows; i++)
	{
		matrix[i] = (int *)malloc(sizeof(int)*columns);
	}

}

int main(int agrc, char *argv[])
{
	FILE *f;
	f = fopen(argv[1], "r");
	
	int rows;
	int columns;
	int i;
	int j;
	int m;
	int k;
	int curNum;
	// get first matrix
	fscanf(f, "%d\t%d", &rows, &columns);
	int **matOne = (int **)malloc(sizeof(int *)*rows);
	mallocMat(rows, columns, matOne);
	m = rows;
	int cols = columns;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			fscanf(f, "%d\t", &curNum);
			matOne[i][j] = curNum;
		}
		fscanf(f, "\n");
	}
	
	// get second matrix
	fscanf(f, "%d\t%d", &rows, &columns);
	int **matTwo = (int **)malloc(sizeof(int *)*rows);
	mallocMat(rows, columns, matTwo);
	k = columns;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			fscanf(f, "%d\t", &curNum);
			matTwo[i][j] = curNum;
		}
		fscanf(f, "\n");
	}
	// check dimensions
	if(cols != rows)
	{
		printf("bad-matrices");
	}
	else
	{
		int **result = (int **)malloc(sizeof(int *)*m);
		mallocMat(m, k, result);
		matMult(matOne, matTwo, result, m, k, cols);

		// out
		for(i = 0; i < m; i++)
		{	
			for(j = 0; j < k; j++)
			{
				printf("%d\t", result[i][j]);
			}		
			printf("\n");
		}	
	}
	return 0;
}

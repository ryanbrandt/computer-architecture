#include <stdio.h>

void merge(int arr[], int left, int mid, int right)
{	
	int i, j, k;
	/* init space and arrays */
	int ln = mid - left + 1, rn = right - mid;
	int l[ln], r[rn];

	/* copy left and right into temp arrays */
	for(i = 0; i < ln; i++){
		l[i] = arr[left + i];
	}
	for(j = 0; j < rn; j++){
		r[j] = arr[mid + 1 + j];
	}

	i = 0, j = 0, k = left;
	/* merge */
	while(i < ln && j < rn){
		if(l[i] < r[j]){
			arr[k] = l[i];
			i++;
		} else {
			arr[k] = r[j];
			j++;
		}
		k++;
	}
	while(i < ln){
		arr[k] = l[i];
		i++; 
		k++;
	}
	while(j < rn){
		arr[k] = r[j];
		j++; 
		k++;
	}
}
/* recursive split then merge */
void mergeSort(int arr[], int left, int right)
{	
	if(left < right){
		int mid = left+(right-left)/2;
		
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		
		merge(arr, left, mid, right);
	}
}
/* sort evens ascending odds descending */
void evensFirst(int arr[], int n)
{
	/* copy array */
	int i;
	int tmp[n];
	for(i = 0; i < n; i++){
		tmp[i] = arr[i];
	}
	/* do evens ascending */
	int k = 0;
	for(i = 0; i < n; i++){
		if(tmp[i] % 2 == 0){
			arr[k] = tmp[i];
			k++;
		}
	}
	/* do odds descending */
	k = n-1;
	for(i = 0; i < n; i++){
		if(tmp[i] % 2 != 0){
			arr[k] = tmp[i];
			k--;
		}
	}
}

int main(int argc, char *argv[])
{
	/* open file selected */
	FILE *f;
	f = fopen(argv[1], "r");

	/* get size and array contents */
	int n;
	fscanf(f, "%d", &n);
	int arr[n];
	int i = 0;
	while(i < n){
		fscanf(f, "%d\t", &arr[i]);
		i++;
	}
	/* merge sort and check */
	mergeSort(arr, 0, n-1);
	/* put evens ascending then odds descending */
	evensFirst(arr, n);
	i = 0;
	while(i < n){
		printf("%d\t", arr[i]);
		i++;
	}
	return 0;
}

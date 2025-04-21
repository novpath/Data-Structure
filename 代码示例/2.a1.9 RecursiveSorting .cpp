#include <stdio.h>
#include <stdlib.h>

void RecursiveSelectionSort(int a[], int n)
{
	if (n <= 0)
		return ;
	int max_index = 0;
	
	for (int i = 1; i <= n; i++) {
		if (a[i] > a[max_index])
			max_index = i;
	}
	int tmp = a[n];
    a[n] = a[max_index];
    a[max_index] = tmp;
	
	RecursiveSelectionSort(a, n - 1);
}

void MergeSort(int q[], int l, int r)
{
    if (l >= r) return;
    int tmp[r - l];

    int mid = (l + r) >> 1;
    MergeSort(q, l, mid);
    MergeSort(q, mid + 1, r);
    
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];
    
    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
}

int main()
{
	int a[10];
	int n = 9;
	for (int i = 0; i < 10; i++) {
		a[i] = 10 - i;
	}
	
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	
	//RecursiveSelectionSort(a, n);
	MergeSort(a, 0, n);
	
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	
    return 0;
}


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

void MergeSort(int a[], int l, int r)
{
    if (l >= r) return;
    int tmp[r - l + 1];

    int mid = (l + r) >> 1;
    MergeSort(a, l, mid);                     // 递归处理左半区间
    MergeSort(a, mid + 1, r);                 // 递归处理右半区间
    
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)                // 双指针合并有序区间
        if (a[i] <= a[j]) tmp[k++] = a[i++];  // 稳定排序：当元素相等时优先取左半部分
        else tmp[k++] = a[j++];
    
    while (i <= mid) tmp[k++] = a[i++];       // 处理左区间剩余元素
    while (j <= r) tmp[k++] = a[j++];         // 处理右区间剩余元素
    
    for (i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];  // 将排序结果从临时数组写回原数组
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


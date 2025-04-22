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
    MergeSort(a, l, mid);                     // �ݹ鴦���������
    MergeSort(a, mid + 1, r);                 // �ݹ鴦���Ұ�����
    
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)                // ˫ָ��ϲ���������
        if (a[i] <= a[j]) tmp[k++] = a[i++];  // �ȶ����򣺵�Ԫ�����ʱ����ȡ��벿��
        else tmp[k++] = a[j++];
    
    while (i <= mid) tmp[k++] = a[i++];       // ����������ʣ��Ԫ��
    while (j <= r) tmp[k++] = a[j++];         // ����������ʣ��Ԫ��
    
    for (i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];  // ������������ʱ����д��ԭ����
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


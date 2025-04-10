#include <stdio.h>

void ReverseArr(int A[], int left, int right, int n)
{
    int temp;
    if (left >= right || right >= n)
        return;
    for (int i = left; i <= (left + right) / 2; i++) {
        temp = A[i];                                  // 对称交换两端
        A[i] = A[right + left - i];                   // 右端第一个交换元素是A[right + left - i]
        A[right + left - i] = temp;
    }
}

void ArrRotateLeft(int A[], int p, int n)
{
    ReverseArr(A, 0, p - 1, n);
    ReverseArr(A, p, n - 1, n);
    ReverseArr(A, 0, n - 1, n);
}

int main()
{
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	ArrRotateLeft(a, 4, 10);
	for(int i = 0; i < 10; i++)
	    printf("%d ", a[i]);
	return 0;
}

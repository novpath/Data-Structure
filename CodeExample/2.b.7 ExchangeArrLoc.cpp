#include <stdio.h>

typedef int ElementType;

void ReverseArr(ElementType A[], int left, int right, int ArraySize)
{
    ElementType temp;
    if(left >= right || right >= ArraySize)
        return;
    for(int i = left; i <= (left + right) / 2; i++) {
        temp = A[i];                      // 对称交换两端
        A[i] = A[right + left - i];       // 右端第一个交换元素是A[right + left - i]
        A[right + left - i] = temp;
    }
}

void ExchangeArrLoc(ElementType A[], int m, int n, int ArraySize)
{
    ReverseArr(A, 0, m - 1, ArraySize);
    ReverseArr(A, m, m + n - 1, ArraySize);
    ReverseArr(A, 0, m + n - 1, ArraySize);
}

int main()
{
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	ExchangeArrLoc(a, 9, 1, 10);
	for(int i = 0; i < 10; i++)
	    printf("%d ", a[i]);
	return 0;
}

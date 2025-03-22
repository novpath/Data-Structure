#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50    //����󳤶ȵĶ���

typedef int ElementType;

void SearchExchangeInsert(ElementType A[], int &n, ElementType x);

int main()
{
	int n = 10;
    int a[MAXSIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    
    SearchExchangeInsert(a, n, 11); 
    
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}

void SearchExchangeInsert(ElementType A[], int &n, ElementType x)
{
    int low = 0, high = n - 1, mid;       // n Ϊ˳�����, low �� high Ϊ���� A[] ���±귶Χ
    while (low <= high) {
        mid = (low + high) / 2;        
        if (x == A[mid])
            break;
        else if (x < A[mid])              // x С���м�ֵ����ȥ���Ѱ��
            high = mid - 1;
        else                              // x �����м�ֵ����ȥ�Ұ�Ѱ��
            low = mid + 1;
    }
    if (low <= high && mid != n - 1) {    // ���ҵ�Ŀ�� x���Ҳ�Ϊ��β����ͺ��Ԫ�ؽ���
        ElementType temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    int i;
    if (low > high) {                     // δ���ҵ�����Ӻ�߿�ʼ���ƣ��ڳ�λ�ò��� x
        for (i = n - 1; i > high; i--) 
            A[i + 1] = A[i];
        A[i + 1] = x;
        n++;                              // ����һ 
    }
}


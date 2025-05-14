#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50    //表最大长度的定义

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
    int low = 0, high = n - 1, mid;       // n 为顺序表长度, low 和 high 为数组 A[] 的下标范围
    while (low <= high) {
        mid = (low + high) / 2;        
        if (x == A[mid])
            break;
        else if (x < A[mid])              // x 小于中间值，则去左半寻找
            high = mid - 1;
        else                              // x 大于中间值，则去右半寻找
            low = mid + 1;
    }
    if (low <= high && mid != n - 1) {    // 查找到目标 x，且不为表尾，则和后继元素交换
        ElementType temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    int i;
    if (low > high) {                     // 未查找到，则从后边开始后移，腾出位置插入 x
        for (i = n - 1; i > high; i--) 
            A[i + 1] = A[i];
        A[i + 1] = x;
        n++;                              // 表长加一 
    }
}


#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50    //表最大长度的定义

typedef int ElementType;

void PrintSameN(ElementType A[], ElementType B[], ElementType C[], int n)
{
    int i = 0, j = 0, k = 0;                     // 初始化三个工作指针
    while (i < n && j < n && k < n) {            // 相同则输出，并集体后移
        if (A[i] == B[j] && B[j] == C[k]) {
            printf("%d\n", A[i]);
            i++; j++; k++;
        } else {
            if (A[i] < B[j] || A[i] < C[k]) i++; // A[i]不是最大就让 i++
            if (B[j] < A[i] || B[j] < C[k]) j++; // B[j]不是最大就让 j++
            if (C[k] < A[i] || C[k] < B[j]) k++; // C[k]不是最大就让 k++
        }
    }
}
int main()
{
	const int n = 4;
    int a[n] = {1, 2, 3, 6};
    int b[n] = {2, 3, 4, 5};
    int c[n] = {-1, 0, 2, 3};
    
    PrintSameN(a, b, c, n); 
    
    return 0;
}



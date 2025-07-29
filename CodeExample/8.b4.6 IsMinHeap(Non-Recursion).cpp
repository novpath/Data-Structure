#include <cstdio>

#define NULL nullptr

bool IsMinHeap(int A[], int k, int len)
{
    if (len % 2 == 0) {                        //len 为偶数,有一个单分支结点
        if (A[len / 2] > A[len])               //判断单分支结点
            return false;
        for (int i = len / 2 - 1; i >= 1; i--) //判断所有双分支结点
            if (A[i] > A[2 * i] || A[i] > A[2 * i + 1])
                return false;
    } else {                                   //len 为奇数时,没有单分支结点
        for (int i = len / 2; i >= 1; i--)     //判断所有双分支结点
            if (A[i] > A[2 * i] || A[i] > A[2 * i + 1])
                return false;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    printf("%s", IsMinHeap(A, 1, n) ? "Yes" : "No");

    return 0;
}

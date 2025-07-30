#include <cstdio>

typedef int ElementType;

void InsertSort(ElementType A[], int m, int n)
{
    for (int i = m + 1; i <= m + n; i++) {// 依次将 A[m+1..m+n]插入有序表
        int j;
        A[0] = A[i];                      // 复制为哨兵
        for (j = i - 1; A[j] > A[0]; j--) // 从后往前插入
            A[j + 1] = A[j];              // 元素后移
        A[j + 1] = A[0];                  // 插入
    }
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int A[m + n];
    for (int i = 1; i <= m; i++)
        scanf("%d", &A[i]);
    for (int i = m + 1; i <= m + n; i++)
        scanf("%d", &A[i]);

    InsertSort(A, m, n);
    for (int i = 1; i <= m + n; i++)
        printf("%d ", A[i]);

    return 0;
}

#include <cstdio>

typedef int ElementType;

void ShellSort(ElementType A[], int n)
{
    // A[0] 只是暂存单元，不是哨兵，当 j<=0时，插入位置已到
    int dk, i, j;
    for (dk = n / 2; dk >= 1; dk = dk / 2)     // 增量变化(无统一规定，希尔建议是每次增量缩小一半)
        for (i = dk + 1; i <= n; ++i)
            if (A[i] < A[i - dk]) {            // 需将 A[i]插入有序增量子表
                A[0] = A[i];                   // 暂存在 A[0]
                for (j = i - dk; j > 0 && A[0] < A[j]; j -= dk)
                    A[j + dk] = A[j];          // 记录后移，查找插入的位置
                A[j + dk] = A[0];              // 插入
            }
}

int main()
{
    int A[14] = {0, 48, 27, 96, 48, 25, 6, 90, 17, 84, 62, 49, 72, 17};
    ShellSort(A, 13);
    for (int i = 1; i <= 13; ++i)
        printf("%d ", A[i]);
    return 0;
}

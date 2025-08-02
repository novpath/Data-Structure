#include <stdio.h>
#define Cutoff 10         // 定义Cutoff阈值（小规模数据用插入排序）
typedef int ElementType;  // 定义元素类型（可根据需要修改，如float、char等）

// 交换两个元素
void Swap(ElementType *a, ElementType *b)
{
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

// 插入排序（处理小规模数据）
void InsertionSort(ElementType A[], int N)
{
    for (int i = 1; i < N; i++) {
        int j;
        ElementType temp = A[i];
        for (j = i; j > 0 && A[j - 1] > temp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}

// 三数取中选基准
ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center]) Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right]) Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right]) Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right - 1]);
    return A[Right - 1];
}

// 核心递归排序函数
void Qsort(ElementType A[], int Left, int Right)
{
    if (Cutoff <= Right - Left) {
        int Pivot = Median3(A, Left, Right);
        int Low = Left;
        int High = Right - 1;
        while (1) {
            while (A[++Low] < Pivot);
            while (A[--High] > Pivot);
            if (Low < High) Swap(&A[Low], &A[High]);
            else break;
        }
        Swap(&A[Low], &A[Right - 1]);
        Qsort(A, Left, Low - 1);
        Qsort(A, Low + 1, Right);
    } else {
        InsertionSort(A + Left, Right - Left + 1);
    }
}

// 统一调用接口
void QuickSort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}

// 测试用例
int main()
{
    ElementType arr[] = {8, 34, 51, 21, 18, 64, 26, 32};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before Quick Sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    QuickSort(arr, n);

    printf("After Quick Sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

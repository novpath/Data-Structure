#include <stdio.h>
#define MaxM 10
typedef int ElementType;

void InsertionSort(ElementType A[], int N)
{  /* 插入排序 */
    for (int i = 1; i < N; i++) {
        int j;
        ElementType temp = A[i];  /* 取出未排序序列中的第一个元素 */
        for (j = i; (j > 0) && (temp > A[j - 1]); j--) A[j] = A[j - 1];  /* 依次与已排序序列中元素比较并右移 */
        A[j] = temp;  /* 放进合适的位置 */
    }
}

void Adjust(ElementType A[], int i, int N)
{  /* 对A[]中的前N个元素从第i个元素开始向下迁移调整（最小堆调整） */
    int Child;
    ElementType temp;
    for (temp = A[i]; (2 * i + 1) < N; i = Child) {
        Child = (2 * i + 1);  /* 左孩子结点 */
        if (Child + 1 != N && A[Child + 1] < A[Child])  /* 选择左、右孩子中较小的结点 */
            Child++;
        if (temp > A[Child]) A[i] = A[Child];  /* 移动Child元素到上层 */
        else break;
    }
    A[i] = temp;  /* 将temp放到当前位置 */
}

int main()
{
    int N, M, i;
    ElementType A[MaxM], temp;
    scanf("%d %d", &N, &M);
    if (N > MaxM) {  /* 当数据量超过MaxM时，使用最小堆筛选最大的M个元素 */
        for (i = 0; i < M; i++) scanf("%d", &A[i]);
        /* 建立最小堆 */
        for (i = (M - 1) >> 1; i >= 0; i--) Adjust(A, i, M);
        /* 处理剩余N-M个元素，替换堆顶（最小元）并调整堆 */
        for (i = M; i < N; i++) {
            scanf("%d", &temp);  /* 读入剩下的数据 */
            if (temp > A[0]) {  /* 如果新数据比堆顶（最小元）大 */
                A[0] = temp;  /* 替换最小元 */
                Adjust(A, 0, M);  /* 调整最小堆 */
            }
        }
        /* 对堆中的M个元素进行堆排序（降序） */
        for (i = M - 1; i > 0; i--) {
            /* 将堆顶元素（最小元）与当前堆的最后一个元素交换 */
            temp = A[0];
            A[0] = A[i];
            A[i] = temp;
            /* 调整剩余i个元素为最小堆 */
            Adjust(A, 0, i);
        }
    } else {  /* 当数据量N <= MaxM时，使用插入排序（降序） */
        for (i = 0; i < N; i++)  /* 注：原代码此处可能漏写i<，修正为i < N */
            scanf("%d", &A[i]);
        InsertionSort(A, N);  /* 调用插入排序 */
    }
    /* 输出结果 */
    if (N < M) M = N;  /* 如果N < M，输出所有N个元素 */
    printf("%d", A[0]);
    for (i = 1; i < M; i++)
        printf(" %d", A[i]);
    printf("\n");
    return 0;
}

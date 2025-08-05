#include <cstdio>
#include <cstdlib>

typedef int ElementType;
int n = 13; // 数组长度（假设已定义且为全局变量或通过参数传入）
ElementType *B = (ElementType *) malloc((n + 1) * sizeof(ElementType)); // 辅助数组（需确保大小≥n）
// 合并两个有序子序列 A[low...mid] 和 A[mid+1...high]（用户提供的Merge函数）
void Merge(ElementType A[], int low, int mid, int high)
{
    int i, j, k;
    for (k = low; k <= high; k++)
        B[k] = A[k]; // 将A中待合并区间复制到辅助数组B
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++) {
        if (B[i] <= B[j])  // 比较B中两个子序列的元素，取较小值放入A
            A[k] = B[i++];
        else
            A[k] = B[j++];
    }
    while (i <= mid) A[k++] = B[i++];  // 处理第一个子序列剩余元素
    while (j <= high) A[k++] = B[j++]; // 处理第二个子序列剩余元素
}

// 非递归归并排序（从底向上合并）
void MergeSort(ElementType A[], int n)
{
    if (n <= 1) return; // 数组长度≤1时无需排序
    for (int len = 1; len < n; len *= 2) { // 子序列长度迭代，直至覆盖整个数组
        // 遍历数组，两两合并长度为len的子序列
        for (int low = 0; low + len < n; low += 2 * len) {  // low 为每次合并的起始位置
            int mid = low + len - 1;       // 第一个子序列的末尾索引
            int high = low + 2 * len - 1;  // 第二个子序列的末尾索引（可能越界）
            if (high >= n) high = n - 1;   // 修正越界的high（确保不超过数组范围）
            Merge(A, low, mid, high);      // 合并两个有序子序列
        }
    }
}

int main()
{
    int A[n] = {48, 27, 96, 48, 25, 6, 90, 17, 84, 62, 49, 72, 17};
    MergeSort(A, n);
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    return 0;
}

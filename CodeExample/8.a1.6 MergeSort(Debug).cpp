#include <cstdio>
#include <cstdlib>

typedef int ElementType;
int n = 13;
int totalCmpCnt = 0, totalSwapCnt = 0;
ElementType *B = (ElementType *) malloc((n + 1) * sizeof(ElementType)); //辅助数组 B
void Merge(ElementType A[], int low, int mid, int high)
{
    int cmpCnt = 0, swapCnt = 0;
    //表 A 的两段 A [low...mid] 和 A [mid+1...high] 各自有序，将它们合并成一个有序表
    printf("low = %d, high = %d\n", low, high);
    int i, j, k;
    for (k = low; k <= high; k++)
        B[k] = A[k];             // 将 A 中所有元素复制到 B 中
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
        if (cmpCnt++ && B[i] <= B[j]) {
            // 比较B的两个段中的元素
            A[k] = B[i++];
            ++swapCnt;
        }       // 将较小值复制到 A 中
        else {
            A[k] = B[j++];
            ++swapCnt;
        }
    }
    while (i <= mid) {
        A[k++] = B[i++];
        ++swapCnt;
    }   // 若第一个表未检测完，复制
    while (j <= high) {
        A[k++] = B[j++];
        ++swapCnt;
    }  // 若第二个表未检测完，复制
    printf("cmpCnt = %d, swapCnt = %d\n", cmpCnt, swapCnt);
    for (int m = 0; m < n; m++) {
        printf("%d,", A[m]);
    }
    printf("\n\n");
    totalCmpCnt += cmpCnt;
    totalSwapCnt += swapCnt;
}

void MergeSort(ElementType A[], int low, int high)
{
    if (low < high) {                // 只剩下一个元素时不需要排
        int mid = (low + high) / 2;  // 从中间划分两个子序列
        MergeSort(A, low, mid);      // 对左侧子序列进行递归排序
        MergeSort(A, mid + 1, high); // 对右侧子序列进行递归排序
        Merge(A, low, mid, high);    // 归并
    }
}

int main()
{
    int A[n] = {48, 27, 96, 48, 25, 6, 90, 17, 84, 62, 49, 72, 17};
    MergeSort(A, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n%d %d", totalCmpCnt, totalSwapCnt);

    return 0;
}

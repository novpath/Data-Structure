#include <stdio.h>

void MergeSort(int a[], int l, int r)
{
    if (l >= r) return;
    int tmp[r - l + 1];

    int mid = (l + r) >> 1;
    MergeSort(a, l, mid);                     // 递归处理左半区间
    MergeSort(a, mid + 1, r);                 // 递归处理右半区间
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)                // 双指针合并有序区间
        if (a[i] <= a[j]) tmp[k++] = a[i++];  // 稳定排序：当元素相等时优先取左半部分
        else tmp[k++] = a[j++];
    while (i <= mid) tmp[k++] = a[i++];       // 处理左区间剩余元素
    while (j <= r) tmp[k++] = a[j++];         // 处理右区间剩余元素
    for (i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];  // 将排序结果从临时数组写回原数组
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    MergeSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i != n - 1 ? ' ' : '\n');

    return 0;
}

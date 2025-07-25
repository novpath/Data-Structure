#include <cstdio>

int SetPartition(int a[], int n)
{
    int low = 0, low0 = 0, high = n - 1, high0 = n - 1, flag = 1, k = n / 2, i;
    int s1 = 0, s2 = 0;
    while (flag) {
        int pivot = a[low];             // 选择枢轴
        while (low < high) {            // 基于枢轴对数据进行划分
            while (low < high && a[high] >= pivot) --high;
            if (low != high) a[low] = a[high];
            while (low < high && a[low] <= pivot) ++low;
            if (low != high) a[high] = a[low];
        } //end of while(low<high)
        a[low] = pivot;
        if (low == k - 1) // 若枢轴是第 n/2 小的元素,划分成功
            flag = 0;
        else {            // 是否继续划分
            if (low < k - 1) {
                low0 = ++low;
                high = high0;
            } else {
                high0 = --high;
                low = low0;
            }
        }
    }
    for (i = 0; i < k; i++) s1 += a[i];
    for (i = k; i < n; i++) s2 += a[i];
    return s2 - s1;
}

int main()
{
    int a[10] = {3, 2, 4, 1, 5, 0, 7, 9, 6, 8};
    int size = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < size; i++)
        printf("%d%c", a[i], i == size - 1 ? '\n' : ' ');
    printf("%d\n", SetPartition(a, size));
    for (int i = 0; i < size; i++)
        printf("%d%c", a[i], i == size - 1 ? '\n' : ' ');
    return 0;
}

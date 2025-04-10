/* PTA 进阶实验 1-3.1 两个有序序列的中位数 OJ 已验证*/

#include <stdio.h>

int SearchMedian(int A[], int B[], int n)
{
    int i = 0, j = 0;                // 工作指针 i，j
    while (i < n && j < n) {         // 处理两个序列
        if (A[i] < B[j]) {           
            if (i + j == n - 1) {    // 已达中间位置，且 A[i] 比 B[j] 小
                return A[i];
            }
            i++;
        } else {
            if (i + j == n - 1) {    // 已达中间位置，且 B[j] 比 A[i] 小
                return b[j];
            }
            j++;
        }
    }
}

int M_Search(int A[], int B[], int n) { // n 即为序列长度 L
    int s1 = 0, e1 = n - 1, mid1, s2 = 0, e2 = n - 1, mid2;
    while (s1 != e1 || s2 != e2) {
        mid1 = (s1 + e1) / 2;
        mid2 = (s2 + e2) / 2;
        if (A[mid1] == B[mid2]) {
            return A[mid1];
        } else if (A[mid1] < B[mid2]) { // 分别考虑奇数和偶数，保持两个子数组元素个数相等
            if ((s1 + e1) % 2 == 0) {   // 若元素个数为奇数
                s1 = mid1;              // 舍弃 A 中间点以前的部分
                e2 = mid2;              // 舍弃 B 中间点以后的部分
            } else {                    // 若元素个数为偶数
                s1 = mid1 + 1;          // 舍弃 A 中间点及中间点以前的部分
                e2 = mid2;              // 舍弃 B 中间点以后的部分
            }
        } else {                      // 分别考虑奇数和偶数，保持两个子数组元素个数相等
            if ((s1 + e1) % 2 == 0) { // 若元素个数为奇数
                e1 = mid1;            // 舍弃 A 中间点以后的部分
                s2 = mid2;            // 舍弃 B 中间点以前的部分
            } else {                  // 若元素个数为偶数
                e1 = mid1;            // 舍弃 A 中间点以后的部分
                s2 = mid2 + 1;        // 舍弃 B 中间点及中间点以前的部分
            }
        }
    }
    return A[s1] < B[s2] ? A[s1] : B[s2];
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int a[n], b[n];
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(i = 0; i < n; i++)
        scanf("%d", &b[i]);
    //printf("%d", SearchMedian(a, b, n));
    printf("%d", M_Search(a, b, n));
    return 0;
}

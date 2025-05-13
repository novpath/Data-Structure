#include <stdio.h>

void LongestIncreSeq(int a[], int &begin, int &end, int n)
{
    int i;
    int s,t;
    begin = end = s = t = 0;
    int MaxLength = 1;
    for (i = 1; i < n; i++) {
        if (a[i] > a[i - 1]) // 序列递增则更新右端点
            t = i;           
        else                 // 如果当前元素不为递增，则不可能是最长递增子列的元素，抛弃之
            s = t = i;
        if ((t - s + 1) > MaxLength) {  // 如果当前递增子列最长，则更新最长长度以及数列端点序号
            MaxLength = t - s + 1;
            begin = s;
            end = t;
        }
    }
}

int main()
{
    int n, begin, end;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    LongestIncreSeq(a, begin, end, n);
    for (int i = begin; i <= end; i++) {
        printf("%d", a[i]);
        if (i != end)
            printf(" ");
    }
    printf("\n");

    return 0;
}

#include <stdio.h>

/* leetcode 41 ȱʧ�ĵ�һ������ */

int FirstMissingPositive(int A[], int n)
{
    int i, B[n + 2];
    for (i = 1; i <= n + 1; i++)
        B[i] = 0;
    for (i = 0; i < n; i++) {
        if(A[i] > 0 && A[i] <= n)
            B[A[i]] = 1;
    }
    i = 1;
    while(B[i] != 0)              // B[n + 1]Ϊ 0����Ϊ�ڱ������ã�������ൽ n + 1 ֹͣ
        i++;
    return i;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int a[n];
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("%d", FirstMissingPositive(a, n));
    return 0;
}

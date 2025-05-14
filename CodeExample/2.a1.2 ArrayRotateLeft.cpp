#include <stdio.h>

void ArrayReverse(int A[], int left, int high)
{
    if (left >= high)
        return ;
    int len = high - left;
    int temp;
    for (int i = 0; i <= len / 2; i++) {
        temp = A[left + i];
        A[left + i] = A[high - i];
        A[high - i] = temp;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    
    m = m % n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    ArrayReverse(a, 0, m - 1);
    ArrayReverse(a, m, n - 1);
    ArrayReverse(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1)
            printf(" ");
    }

    return 0;
}

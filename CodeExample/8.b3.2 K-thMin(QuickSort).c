#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSort(int q[], int l, int r)
{
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        while (q[++i] < x);
        while (q[--j] > x);
        if (i < j) swap(&q[i], &q[j]);
    }
    QuickSort(q, l, j);
    QuickSort(q, j + 1, r);
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    QuickSort(a, 0, n - 1);
    printf("%d", a[k - 1]);
    return 0;
}

#include<stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int QuickSelect(int *q, int l, int r, int k)
{
    if (l >= r) return q[l];
    int i = l - 1, j = r + 1, x = q[i + j >> 1];
    while (i < j) {
        while (q[++i] < x);
        while (q[--j] > x);
        if (i < j) swap(&q[i], &q[j]);
    }
    int sl = j - l + 1;
    if (k <= sl)
        return QuickSelect(q, l, j, k);
    return QuickSelect(q, j + 1, r, k - sl);
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int q[n];
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);
    printf("%d", QuickSelect(q, 0, n - 1, k));

    return 0;
}

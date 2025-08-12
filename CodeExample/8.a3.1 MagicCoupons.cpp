#include <cstdio>
#include <cstdlib>

int CompInt(const void *a, const void *b)
{
    return *(const int *) b - *(const int *) a;
}

int main()
{
    int n, m;
    scanf("%d", &n);
    int A[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    scanf("%d", &m);
    int B[m];
    for (int i = 0; i < m; i++)
        scanf("%d", &B[i]);
    qsort(A, n, sizeof(A[0]), CompInt);
    qsort(B, m, sizeof(B[0]), CompInt);
    int total = 0;
    int i, j, k, l;
    for (i = 0, j = 0; i < n && j < m && A[i] * B[j] > 0; i++, j++)
        total += A[i] * B[j];
    for (k = n - 1, l = m - 1; k >= i && l >= j && A[k] * B[l] > 0; k--, l--)
        total += A[k] * B[l];
    printf("%d\n", total);
    return 0;
}

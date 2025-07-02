#include <cstdio>

#define OrderOfMatrix 3

void OrderedMatrixSearch(int a[][OrderOfMatrix], int &m, int &n, int key)
{
    m = 0;
    n = OrderOfMatrix - 1;
    while (m < OrderOfMatrix && n >= 0) {
        if (a[m][n] == key)
            return;
        if (key < a[m][n])
            n--;
        else
            m++;
    }
    m = n = -1;
}

int main()
{
    int A[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    int m, n;
    OrderedMatrixSearch(A, m, n, 8);
    printf("m = %d, n = %d", m, n);

    return 0;
}

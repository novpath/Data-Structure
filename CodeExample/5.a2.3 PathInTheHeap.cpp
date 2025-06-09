#include <cstdio>
#define NULL nullptr

#define MAXN 1001
#define MINH (-10001)

int H[MAXN], size;

void Create()
{
    size = 0;
    H[0] = MINH;    // 设置“岗哨”
}

void Insert(int x)
{
    if (size == MAXN)
        return;
    int i;
    for (i = ++size; H[i / 2] > x; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

int main()
{
    int n, m, x, i, j;
    scanf("%d %d", &n, &m);
    Create();                       // 堆初始化
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        Insert(x);
    }
    for (i = 0; i < m; i++) {
        scanf("%d", &j);
        while (j > 0) {
            printf("%d", H[j]);
            j /= 2;
            if (j > 0)
                printf(" ");
        }
        if (i != m - 1)
            printf("\n");
    }

    return 0;
}

#include <stdio.h>
#define MaxSize 1000

typedef struct sqstack {
    int data[MaxSize];
    int top;
} sqstack;

int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    int a[n];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[j]);
        }
        sqstack s;
        s.top = -1;
        int valid = 1;
        int current = 1;               // 入栈数字
        for (int j = 0; j < n; j++) {
            while (a[j] >= current) {
                if (s.top == m - 1) {
                    valid = 0;
                    break;
                }
                s.data[++s.top] = current++;
            }
            if (s.top == -1 || a[j] != s.data[s.top--]) {
                valid = 0;
                break;
            }
        }
        if (s.top != -1)
            valid = 0;
        printf(valid ? "YES" : "NO");
        if (i != k - 1)
            printf("\n");
    }

    return 0;
}
#include <stdio.h>

int main()
{
    int N, i, j, cnt = 0;
    scanf("%d", &N);
    int a[N], b[N];
    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        b[i] = 0;
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (a[i] <= 100 - b[j]) {
                b[j] += a[i];
                printf("%d %d\n", a[i], j + 1);
                if (j + 1 > cnt)
                    cnt = j + 1;
                break;
            }
        }
    }
    printf("%d", cnt);

    return 0;
}


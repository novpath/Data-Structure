#include <stdio.h>
#define MaxM 51

int main()
{
    int N, Count[MaxM], i, K;
    /* 初始化 Count [] */
    for (i = 0; i < MaxM; i++)Count[i] = 0;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &K);
        Count[K]++;/* 工龄为 K 的计数器加 1 */
    }
    for (K = 0; K < MaxM; K++)
        if (Count[K])
            printf("%d:%d\n", K, Count[K]);
    return 0;
}

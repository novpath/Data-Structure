#include <cstdio>
#include <stdlib.h>

#define MaxLength 100

typedef struct SqNode {
    int a[MaxLength];
    int length;
} SqNode, *SqList;

int SearchAndSwap(SqList L, int x)
{
    int i = -1;
    while (i < L->length && L->a[i] != x)
        i++;
    if (i >= 1) {
        int t = L->a[i - 1];
        L->a[i - 1] = L->a[i];
        L->a[i] = t;
        i--;
    }
    return i;
}

int main()
{
    SqList L = (SqList) malloc(sizeof(SqList));
    L->a[0] = 3;
    L->a[1] = 7;
    L->a[2] = 9;
    L->a[3] = 11;
    L->length = 4;
    printf("%d", SearchAndSwap(L, 11));

    free(L);
    return 0;
}

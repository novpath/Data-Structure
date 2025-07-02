#include <cstdio>
#include <cstdlib>

#define MaxLength 100

typedef struct SqNode {
    int a[MaxLength];
    int length;
} SqNode, *SqList;

int RecursiveBinarySearch(SqList L, int low, int high, int x)
{
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (L->a[mid] == x)
        return mid;
    if (L->a[mid] > x)
        return RecursiveBinarySearch(L, low, mid - 1, x);
    return RecursiveBinarySearch(L, mid + 1, high, x);
}

int main()
{
    SqList L = (SqList) malloc(sizeof(SqNode));
    L->length = 3;
    L->a[1] = 2;
    L->a[2] = 4;
    L->a[3] = 6;
    printf("%d", RecursiveBinarySearch(L, 1, L->length, 2));

    free(L);
    return 0;
}

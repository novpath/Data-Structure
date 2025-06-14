#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MaxSize 1001
#define NULL nullptr

int min(int a, int b)
{
    return a < b ? a : b;
}

void FindLevelOrder(int inorder[], int l, int h, int level[], int root)
{
    if (l > h)
        return;
    int n = h - l + 1;
    int H = (int) log2(n) + 1;
    int leftSize;
    if (H == 1) {
        leftSize = 0;
    } else {
        int x = n + 1 - (1 << (H - 1));
        leftSize = 1 << (H - 2) - 1 + min(x, 1 << (H - 2));
    }

    level[root] = inorder[l + leftSize];
    int LeftRoot = root * 2 + 1;
    int RightRoot = LeftRoot + 1;
    FindLevelOrder(inorder, l, l + leftSize - 1, level, LeftRoot);
    FindLevelOrder(inorder, l + leftSize + 1, h, level, RightRoot);
}

void InOrderToLevelOrder(int inorder[], int level[], int n)
{
    return FindLevelOrder(inorder, 0, n - 1, level, 0);
}

int ComInt(const void *a, const void *b)
{
    return *(const int *) a - *(const int *) b;
}

int main()
{
    int inorder[MaxSize], level[MaxSize];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    qsort(inorder, n, sizeof(int), ComInt);
    InOrderToLevelOrder(inorder, level, n);
    for (int i = 0; i < n; i++) {
        printf("%d%c", level[i], (i == n - 1) ? '\n' : ' ');
    }

    return 0;
}

#include <cstdio>

typedef struct CartesianTree {
    int k1, k2;
    int left, right;
    int tag;
} CTNode;

int pre = -1, curr;
int IsBST = 1, IsMinHeap = 1;

void InOrder(int root, CTNode CT[])
{
    if (root == -1) return;
    InOrder(CT[root].left, CT);
    curr = CT[root].k1;
    if (pre > curr)
        IsBST = 0;
    pre = curr;
    InOrder(CT[root].right, CT);
}

void PostOrder(int root, CTNode CT[])
{
    if (root == -1) return;
    PostOrder(CT[root].left, CT);
    PostOrder(CT[root].right, CT);
    if (CT[root].left != -1 && CT[root].k2 > CT[CT[root].left].k2 ||
        CT[root].right != -1 && CT[root].k2 > CT[CT[root].right].k2)
        IsMinHeap = 0;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    CTNode CT[n];
    for (i = 0; i < n; i++)
        CT[i].tag = 1;
    for (i = 0; i < n; i++) {
        scanf("%d %d %d %d", &CT[i].k1, &CT[i].k2, &CT[i].left, &CT[i].right);
        if (CT[i].left != -1)
            CT[CT[i].left].tag = 0;
        if (CT[i].right != -1)
            CT[CT[i].right].tag = 0;
    }
    for (i = 0; i < n; i++) {
        if (CT[i].tag == 1)
            break;
    }
    InOrder(i, CT);
    PostOrder(i, CT);
    if (IsBST && IsMinHeap)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}

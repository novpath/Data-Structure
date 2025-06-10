#include <cstdio>

#define null (-1)
#define MaxTree 10
#define Tree int

typedef char ElementType;

struct BiTNode {
    ElementType data;
    Tree lchild, rchild;
} T1[MaxTree], T2[MaxTree];

Tree BuildTree(BiTNode T[]);
bool IsomorphismOfTrees(Tree R1, Tree R2);

int main()
{
    Tree R1 = BuildTree(T1);
    Tree R2 = BuildTree(T2);
    if (IsomorphismOfTrees(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}

Tree BuildTree(BiTNode T[])
{
    int n;
    Tree root = null;
    ElementType cl, cr;
    scanf("%d", &n);
    if (n) {
        int i;
        int check[n];
        for (i = 0; i < n; i++)
            check[i] = 0;
        for (i = 0; i < n; i++) {
            scanf(" %c %c %c", &T[i].data, &cl, &cr);
            if (cl != '-') {
                T[i].lchild = cl - '0';
                check[T[i].lchild] = 1;
            } else {
                T[i].lchild = null;
            }
            if (cr != '-') {
                T[i].rchild = cr - '0';
                check[T[i].rchild] = 1;
            } else {
                T[i].rchild = null;
            }
        }
        for (i = 0; i < n; i++)
            if (!check[i]) break;
        root = i;
    }
    return root;
}

bool IsomorphismOfTrees(Tree R1, Tree R2)
{
    if ((R1 == null) && (R2 == null))
        return true;
    if (R1 == null || R2 == null)
        return false;
    if (T1[R1].data != T2[R2].data)
        return false;
    if (T1[R1].lchild == null && T2[R2].lchild == null)
        return IsomorphismOfTrees(T1[R1].rchild, T2[R2].rchild);
    if ((T1[R1].lchild != null && T2[R2].lchild != null) && (T1[T1[R1].lchild].data == T2[T2[R2].lchild].data))
        return (IsomorphismOfTrees(T1[R1].lchild, T2[R2].lchild) && IsomorphismOfTrees(T1[R1].rchild, T2[R2].rchild));
    return IsomorphismOfTrees(T1[R1].lchild, T2[R2].rchild) && IsomorphismOfTrees(T1[R1].rchild, T2[R2].lchild);
}

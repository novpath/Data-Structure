#include <cstdio>
#define NULL nullptr
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

bool IsBinaryTreeSimilar(BiTree T1, BiTree T2)
{
    if (T1 == NULL && T2 == NULL)
        return true;
    if (T1 == NULL || T2 == NULL)
        return false;
    return IsBinaryTreeSimilar(T1->lchild, T2->lchild) && IsBinaryTreeSimilar(T1->rchild, T2->rchild);
}

int main()
{
    BiTNode a = {1, NULL, NULL};
    BiTNode d = {4, NULL, NULL};
    BiTNode c = {3, NULL, &d};
    BiTNode b = {2, &a, &c};

    BiTNode e = {1, NULL, NULL};
    BiTNode f = {4, NULL, NULL};
    BiTNode g = {3, NULL, &f};
    BiTNode h = {2, &e, &g};

    BiTNode i = {4, NULL, NULL};
    BiTNode j = {3, NULL, NULL};
    BiTNode k = {2, &i, &j};

    printf("%d %d %d\n", IsBinaryTreeSimilar(&a, &d), IsBinaryTreeSimilar(&b, &h), IsBinaryTreeSimilar(NULL, NULL));
    printf("%d", IsBinaryTreeSimilar(&b, &k));
    return 0;
}

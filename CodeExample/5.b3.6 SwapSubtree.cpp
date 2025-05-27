#include <stdio.h>
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void SwapSubtree(BiTree T)
{
    if (T == NULL)
        return;
    SwapSubtree(T->lchild);
    SwapSubtree(T->rchild);
    BiTree t = T->lchild;
    T->lchild = T->rchild;
    T->rchild = t;
}

int main()
{
    /* 测试样例来自 5.b3.f*/
    BiTNode a = {1, NULL, NULL};
    BiTNode d = {4, NULL, NULL};
    BiTNode c = {3, NULL, &d};
    BiTNode b = {2, &a, &c};

    printf("Before SwapSubtree:\n");
    printf("    %d\n", b.data);
    printf("   / \\\n");
    printf("  %d   %d\n", b.lchild->data, b.rchild->data);
    printf("       \\\n");
    printf("        %d\n", c.rchild->data);
    SwapSubtree(&b);
    printf("After SwapSubtree:\n");
    printf("    %d\n", b.data);
    printf("   / \\\n");
    printf("  %d   %d\n", b.lchild->data, b.rchild->data);
    printf(" /\n");
    printf("%d\n", c.lchild->data);

    return 0;
}

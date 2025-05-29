#include <stdio.h>

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void visit(BiTree T)
{
    printf("%d ", T->data);
}

void InOrder(BiTree T)
{
    if (T != NULL) {
        InOrder(T->lchild); // 递归遍历左子树
        visit(T);           // 访问根结点
        InOrder(T->rchild); // 递归遍历右子树
    }
}

int main()
{
    return 0;
}

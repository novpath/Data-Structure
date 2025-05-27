#include <stdio.h>
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

int CountDoubleBranchNode(BiTree T)
{
    if (T == NULL)
        return 0;
    if (T->lchild && T->rchild)
        return 1 + CountDoubleBranchNode(T->lchild) + CountDoubleBranchNode(T->rchild);
    return CountDoubleBranchNode(T->lchild) + CountDoubleBranchNode(T->rchild);
}

int num;

void CountDBranchNode(BiTree T)
{
    if (T == NULL) return;
    if (T->lchild && T->rchild) num++;  // 当前结点是双分支结点，计数+1
    CountDBranchNode(T->lchild);        // 递归处理左子树
    CountDBranchNode(T->rchild);        // 递归处理右子树
}

int main()
{
    BiTNode T = {1, NULL,NULL};
    CountDBranchNode(&T);
    printf("%d %d\n", CountDoubleBranchNode(&T), num);
    BiTNode a = {2, NULL,NULL};
    BiTNode b = {3, NULL, NULL};
    T.rchild = &b;
    num = 0;
    CountDBranchNode(&T);
    printf("%d %d\n", CountDoubleBranchNode(&T), num);
    T.lchild = &a;
    num = 0;
    CountDBranchNode(&T);
    printf("%d %d\n", CountDoubleBranchNode(&T), num);

    return 0;
}

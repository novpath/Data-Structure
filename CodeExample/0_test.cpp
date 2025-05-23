#include <stdio.h>
#include <stdlib.h>
struct ElementType {
    int value;
};

typedef struct BiTNode {
    ElementType data; // 数据域
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

void PostOrder(BiTree T)
{
    if (T != NULL) {
        PostOrder(T->lchild); // 递归遍历左子树
        PostOrder(T->rchild); // 递归遍历右子树
        visit(T); // 访问根结点
    }
}

void LevelOrder(BiTree T)
{
    InitQueue(Q); // 初始化辅助队列
    BiTree p;
    EnQueue(Q, T); // 将根结点入队
    while (!IsEmpty(Q)) { // 队列不空则循环
        DeQueue(Q, p); // 队头结点出队
        visit(p); // 访问出队结点
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild); // 若左孩子不空, 则左孩子入队
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild); // 若右孩子不空, 则右孩子入队
    }
}

int main()
{
    // 定义一棵空树
    BiTree root = NULL;

    // 插入根节点
    root = (BiTree) malloc(sizeof(BiTNode));
    root->lchild = NULL;
    root->rchild = NULL;
    // 插入新结点 2
    BiTNode *p = (BiTNode *) malloc(sizeof(BiTNode));
    p->data = {2};
    p->lchild = NULL;
    p->rchild = NULL;
    root->lchild = p; // 作为根节点的左孩子
    return 0;
}

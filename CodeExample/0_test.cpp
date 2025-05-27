#include <stdio.h>
#include <stdlib.h>

struct ElementType {
    int value;
};

typedef struct BiTNode {
    ElementType data; // 数据域
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

typedef struct node {
    char data[10];
    struct node *left, *right;   // 存储操作数或操作符
} BTree;

typedef struct {              // MAX SIZE 为已定义常量
    int SqBiTNode[MAX_SIZE];  // 保存二叉树结点值的数组
    int ElemNum;              // 实际占用的数组元素个数 SqBiTree;
} SqBiTNode;

// 辅助全局变量，用于查找结点 p 的前驱
BiTNode *p; // p 指向目标结点
BiTNode *pre = NULL; // 指向当前访问结点的前驱
BiTNode *final = NULL; // 用于记录最终结果

// 访问结点 q
void visit(BiTNode *q)
{
    if (q == p) // 当前访问结点刚好是 p
        final = pre; // 找到 p 的前驱
    else
        pre = q; // pre 指向当前访问结点
}

// 中序遍历
void InOrder(BiTree T)
{
    if (T != NULL) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
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

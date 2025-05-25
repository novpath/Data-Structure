#include <stdio.h>

typedef int ElementType;

/* 线索二叉树的结点 */
typedef struct ThreadNode {
    ElementType data;                   // 数据元素
    struct ThreadNode *lchild, *rchild; // 左、右孩子指针
    int ltag, rtag;                     // 左、右线索标志
} ThreadNode, *ThreadTree;

ThreadTree InThread(ThreadTree p, ThreadTree pre)
{
    if (p != NULL) {
        pre = InThread(p->lchild, pre);        // 递归，线索化左子树
        if (p->lchild == NULL) {                  // 当前结点的左子树为空
            p->lchild = pre;                      // 建立当前结点的前驱线索
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) { // 前驱结点非空且其右子树为空
            pre->rchild = p;                      // 建立前驱结点的后继线索
            pre->rtag = 1;
        }
        pre = p;                                  // 标记当前结点成为刚刚访问过的结点
        pre = InThread(p->rchild, pre);        // 递归，线索化右子树
    }
    return pre;
}

void CreateInThread(ThreadTree T)
{
    if (T != NULL) {                // 非空二叉树，线索化
        ThreadTree pre = NULL;
        pre = InThread(T, pre);  // 线索化二叉树
        pre->rchild = NULL;         // 处理遍历的最后一个结点
        pre->rtag = 1;
    }
}

int main()
{
    return 0;
}

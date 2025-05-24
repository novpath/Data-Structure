#include <stdio.h>
typedef int ElementType;
/* 线索二叉树的结点 */
typedef struct ThreadNode {
    ElementType data; // 数据元素
    struct ThreadNode *lchild, *rchild; // 左、右孩子指针
    int ltag, rtag; // 左、右线索标志
} ThreadNode, *ThreadTree;
// 全局变量
ThreadNode *pre = NULL;
void visit(ThreadNode *q);

void PostThread(ThreadTree T)
{
    if (T != NULL) {
        PostThread(T->lchild);
        PostThread(T->rchild);
        visit(T);
    }
}

void visit(ThreadNode *q)
{
    if (q->lchild == NULL) { // 左子树为空，建立前驱线索
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = q; //建立前驱结点的后继线索
        pre->rtag = 1;
    }
    pre = q;
}
// 后序线索化二叉树 T
void CreatePostThread(ThreadTree T)
{
    pre = NULL;       // pre 初始化为 NULL
    if (T != NULL) {  // 非空二叉树才能线索化
        PostThread(T);// 后序线索化二叉树
        if (pre->rchild == NULL)
            pre->rtag = 1; //处理遍历的最后一个结点
    }
}

int main()
{


    return 0;
}
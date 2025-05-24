#include <stdio.h>
typedef int ElementType;
/* 线索二叉树的结点 */
typedef struct ThreadNode {
    ElementType data; // 数据元素
    struct ThreadNode *lchild, *rchild; // 左、右孩子指针
    int ltag, rtag; // 左、右线索标志
} ThreadNode, *ThreadTree;
// 后序线索化
void PostThread(ThreadTree p, ThreadTree &pre)
{
    if (p != NULL) {
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }
}
// 后序线索化二叉树 T
void CreatePostThread(ThreadTree T)
{
    ThreadTree pre = NULL;
    if (T != NULL) {
        PostThread(T, pre);
        if (pre->rchild == NULL)
            pre->rtag = 1;
    }
}

int main() { return 0; }

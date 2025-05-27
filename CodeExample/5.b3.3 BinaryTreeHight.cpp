#include <stdio.h>
#define MaxSize 100
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;                   // 数据域
    struct BiTNode *lchild, *rchild;    // 左、右孩子指针
} BiTNode, *BiTree;

int BTdepth(BiTree T)
{
    if (!T)                        // 树空，高度为 0
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;       // last 指向当前层的最右结点
    BiTree Q[MaxSize];             // 设置队列 Q，元素是二叉树结点指针且容量足够
    Q[++rear] = T;                 // 将根节点入队
    while (front < rear) {         // 队不空，则循环
        BiTree p = Q[++front];     // 队列元素出队，即正在访问的结点
        if (p->lchild)
            Q[++rear] = p->lchild; // 左孩子入队
        if (p->rchild)
            Q[++rear] = p->rchild; // 右孩子入队
        if (front == last) {       // 处理该层的最右结点
            level++;               // 层数增一
            last = rear;           // last 指向下层
        }
    }
    return level;
}

int BinaryTreeHeight(BiTree T)
{
    if (T == NULL)
        return 0;
    return 1 + (BinaryTreeHeight(T->lchild) > BinaryTreeHeight(T->rchild)
                    ? BinaryTreeHeight(T->lchild)
                    : BinaryTreeHeight(T->rchild));
}

int main()
{
    BiTNode T = {1, NULL,NULL};
    printf("%d %d\n", BinaryTreeHeight(&T), BTdepth(&T));
    BiTNode a = {2, NULL,NULL};
    BiTNode b = {3, NULL, NULL};
    T.lchild = &a;
    T.rchild = &b;
    printf("%d %d\n", BinaryTreeHeight(&T), BTdepth(&T));

    return 0;
}

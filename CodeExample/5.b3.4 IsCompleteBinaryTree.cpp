#include <stdio.h>
#define MaxSize 100

typedef struct BiTNode {
    int data;                        // 数据域
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;

typedef BiTree ElementType;

typedef struct {
    ElementType data[MaxSize];  // 用静态数组存放队列元素
    int front, rear;            // 队首指针和队尾指针
} SqQueue;

void InitQueue(SqQueue &Q);
bool QueueEmpty(const SqQueue &Q);
bool EnQueue(SqQueue &Q, ElementType x);
bool DeQueue(SqQueue &Q, ElementType &x);

bool IsCompleteBinaryTree(BiTree T)
{
    if (T == NULL)                    // 空树为满二叉树
        return true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        BiTree p;
        DeQueue(Q, p);
        if (p) {                      // 结点非空，将其左、右子树入队列
            EnQueue(Q, p->lchild);
            EnQueue(Q, p->rchild);
        } else {                      // 结点非空，检查其后是否有非空结点
            while (!QueueEmpty(Q)) {
                DeQueue(Q, p);
                if (p)                // 结点为空，二叉树为非完全二叉树
                    return false;
            }
        }
    }
    return true;
}

int main()
{
    BiTNode T = {1, NULL,NULL};
    printf("%d\n", IsCompleteBinaryTree(&T));
    BiTNode a = {2, NULL,NULL};
    BiTNode b = {3, NULL, NULL};
    T.rchild = &b;
    printf("%d\n", IsCompleteBinaryTree(&T));
    T.lchild = &a;
    printf("%d\n", IsCompleteBinaryTree(&T));

    return 0;
}


void InitQueue(SqQueue &Q)
{
    Q.rear = Q.front = 0;    // 初始化队首、队尾指针
}

bool QueueEmpty(const SqQueue &Q)
{
    if (Q.rear == Q.front)    // 队空条件
        return true;
    return false;
}

bool EnQueue(SqQueue &Q, ElementType x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)   // 队满则报错
        return false;
    Q.data[Q.rear] = x;                      // 将 x 插入队尾
    Q.rear = (Q.rear + 1) % MaxSize;         // 队尾指针加 1 取模
    return true;
}

bool DeQueue(SqQueue &Q, ElementType &x)   // 只能让队头元素出队
{
    if (Q.rear == Q.front)                 // 队空则报错
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;     // 队首指针加 1 取模
    return true;
}

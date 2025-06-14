#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxSize 1001

typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqQueue {
    BiTree data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &Q)
{
    Q.front = Q.rear = 0;
}

bool EnQueue(SqQueue &Q, BiTree e)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, BiTree &e)
{
    if (Q.rear == Q.front)
        return false;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

bool IsQueueEmpty(const SqQueue &Q)
{
    return Q.front == Q.rear;
}

void InOrder(BiTree T, int a[])
{
    static int i = 0;
    if (T) {
        InOrder(T->lchild, a);
        T->data = a[i++];
        InOrder(T->rchild, a);
    }
}

int CompInt(const void *a, const void *b)
{
    return *(const int *) a - *(const int *) b;
}

BiTree BuildCompleteTree(int n)
{
    SqQueue Q;
    InitQueue(Q);
    BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
    BiTree tmp;
    EnQueue(Q, root);
    n--;
    while (n) {
        DeQueue(Q, tmp);
        tmp->lchild = (BiTree) malloc(sizeof(BiTNode));
        *tmp->lchild = {-1, NULL, NULL};
        EnQueue(Q, tmp->lchild);
        n--;
        if (n) {
            tmp->rchild = (BiTree) malloc(sizeof(BiTNode));
            *tmp->rchild = {-1, NULL, NULL};
            EnQueue(Q, tmp->rchild);
            n--;
        }
    }
    return root;
}

void LevelTrav(BiTree root, int a[])
{
    SqQueue Q;
    InitQueue(Q);
    InOrder(root, a);
    EnQueue(Q, root);
    BiTree tmp;
    int first = 1;
    while (!IsQueueEmpty(Q)) {
        DeQueue(Q, tmp);
        if (first == 1) {
            printf("%d", tmp->data);
            first = 0;
        } else {
            printf(" %d", tmp->data);
        }
        if (tmp->lchild)
            EnQueue(Q, tmp->lchild);
        if (tmp->rchild)
            EnQueue(Q, tmp->rchild);
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    if (n <= 0)
        return -1;
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), CompInt);

    LevelTrav(BuildCompleteTree(n), a);

    return 0;
}

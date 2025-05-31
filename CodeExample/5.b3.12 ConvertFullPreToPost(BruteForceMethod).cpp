#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define MaxSize 100

typedef struct BiTNode {
    char data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqQueue {
    BiTree btlink[MaxSize];
    int front, rear;
} SqQueue;

void QueueInit(SqQueue &Q);
bool IsQueueEmpty(const SqQueue &Q);
bool EnQueue(SqQueue &Q, BiTree x);
bool DeQueue(SqQueue &Q, BiTree &x);

void PreOrder(BiTree T, const char PreSeq[])
{
    static int i = 0;
    if (T) {
        T->data = PreSeq[i++];
        PreOrder(T->lchild, PreSeq);
        PreOrder(T->rchild, PreSeq);
    }
}

void PostOrder(BiTree T)
{
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c", T->data);
    }
}

void ConvertFullPreToPost(const char PreSeq[])
{
    int i = 0;
    while (PreSeq[i] != '\0') {
        i++;
    }
    if (i == 0)
        return;
    SqQueue Q;
    QueueInit(Q);
    auto root = static_cast<BiTree>(malloc(sizeof(BiTNode)));
    root->lchild = root->rchild = NULL;
    EnQueue(Q, root);
    i--;
    while (i) {
        BiTree tmp;
        DeQueue(Q, tmp);
        tmp->lchild = static_cast<BiTree>(malloc(sizeof(BiTNode)));
        tmp->lchild->lchild = tmp->lchild->rchild = NULL;
        EnQueue(Q, tmp->lchild);
        i--;
        if (i) {
            tmp->rchild = static_cast<BiTree>(malloc(sizeof(BiTNode)));
            tmp->rchild->lchild = tmp->rchild->rchild = NULL;
            EnQueue(Q, tmp->rchild);
            i--;
        }
    }
    PreOrder(root, PreSeq);
    PostOrder(root);
}


int main()
{
    char str[100];
    scanf("%s", str);
    ConvertFullPreToPost(str);

    return 0;
}

void QueueInit(SqQueue &Q)
{
    Q.front = Q.rear = 0;
}

bool IsQueueEmpty(const SqQueue &Q)
{
    return Q.front == Q.rear;
}

bool EnQueue(SqQueue &Q, BiTree x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.btlink[Q.rear++] = x;
    return true;
}

bool DeQueue(SqQueue &Q, BiTree &x)
{
    if (Q.rear == Q.front)
        return false;
    x = Q.btlink[Q.front++];
    return true;
}

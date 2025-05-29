#include <stdio.h>
#define MaxSize 100

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqStack {
    BiTree data[MaxSize];
    int top;
} SqStack;

void visit(BiTree T)
{
    printf("%d ", T->data);
}

void InorderNonRecursion(BiTree T)
{
    BiTree bt = T;
    SqStack S;
    S.top = -1;
    while (bt || S.top != -1) {
        while (bt) {
            S.data[++S.top] = bt;
            bt = bt->lchild;
        }
        bt = S.data[S.top--];
        visit(bt);
        T = T->rchild;
    }
}

int main()
{
    return 0;
}

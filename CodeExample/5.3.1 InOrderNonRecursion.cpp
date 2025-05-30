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

void InOrderNonRecursion(BiTree T)
{
    BiTree p = T;
    SqStack S;
    S.top = -1;
    while (p || S.top != -1) {
        if (p) {
            S.data[++S.top] = p;
            p = p->lchild;
        } else {
            p = S.data[S.top--];
            visit(p);
            p = p->rchild;
        }
    }
}

int main()
{
    return 0;
}

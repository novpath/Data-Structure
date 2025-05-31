#include <cstdio>

#define  NULL nullptr
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree head, pre = NULL;

BiTree InOrder(const BiTree &T)
{
    if (T) {
        InOrder(T->lchild);
        if (T->rchild == NULL && T->lchild == NULL) {
            if (pre == NULL) {
                head = T;
                pre = T;
            } else {
                pre->rchild = T;
                pre = T;
            }
        }
        InOrder(T->rchild);
        pre->rchild = NULL;
    }
    return head;
}

int main()
{
    BiTNode a = {1, NULL, NULL};
    BiTNode d = {4, NULL, NULL};
    BiTNode c = {3, NULL, &d};
    BiTNode b = {2, &a, &c};

    InOrder(&b);
    while (head) {
        printf("%d ", head->data);
        head = head->rchild;
    }

    return 0;
}

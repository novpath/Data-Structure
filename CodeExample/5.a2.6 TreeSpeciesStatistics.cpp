#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NULL nullptr
typedef char ElementType[31];        // ElementType 定义为字符串

typedef struct BiTNode {
    ElementType name;
    int cnt;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree TreeSpeciesStatics(BiTree T, ElementType name)
{
    if (!T) {
        T = (BiTree) malloc(sizeof(BiTNode));
        strcpy(T->name, name);
        T->cnt = 1;
        T->lchild = NULL;
        T->rchild = NULL;
    } else if (strcmp(name, T->name) < 0) {
        T->lchild = TreeSpeciesStatics(T->lchild, name);
    } else if (strcmp(name, T->name) > 0) {
        T->rchild = TreeSpeciesStatics(T->rchild, name);
    } else {
        T->cnt++;
    }
    return T;
}

int n;

void InOrder(BiTree T)
{
    if (T) {
        InOrder(T->lchild);
        printf("%s %.4lf%%\n", T->name, T->cnt * 1.0 * 100 / n);
        InOrder(T->rchild);
    }
}

int main()
{
    scanf(" %d", &n);
    BiTree T = NULL;
    for (int i = 0; i < n; i++) {
        ElementType name;
        scanf(" %31[^\n]", name);
        T = TreeSpeciesStatics(T, name);
    }
    InOrder(T);
    free(T);
    return 0;
}

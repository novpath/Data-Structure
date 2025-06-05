#include <cstdio>

#define NULL nullptr
#define MaxSize 100

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

int path[MaxSize];
int sum;

void PrintDataValuePath(BiTree T, int &k, const int data)
{
    if (T == NULL)
        return;
    path[k++] = T->data;  // 经过的节点存入路径数组中
    sum += T->data;
    if (sum == data && !T->lchild && !T->rchild) {
        int i = 0;
        while (i < k) {
            printf("%d ", path[i]);
            i++;
        }
        printf("\n");
    }
    PrintDataValuePath(T->lchild, k, data);
    PrintDataValuePath(T->rchild, k, data);
    k--;                    // 回溯至父节点
    sum -= T->data;         // 权值和回溯
}

int main()
{
    BiTNode a = {4, NULL, NULL};
    BiTNode b = {7, NULL, NULL};
    BiTNode c = {5, &a, &b};
    BiTNode d = {12, NULL, NULL};
    BiTNode e = {10, &c, &d};

    int k = 0;
    PrintDataValuePath(&e, k, 22);
    return 0;
}

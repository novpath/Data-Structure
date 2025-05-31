#include <cstdio>
#define NULL nullptr
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *left, *right;
    int weight;
} BiTNode, *BiTree;

int WPL(BiTree T)
{
    if (T == NULL)                                                  // 处理空结点
        return 0;
    if (T->left == NULL && T->right == NULL)
        return 0;
    int wl = WPL(T->left);
    int wr = WPL(T->right);
    // 安全获取左右子结点的权重，避免解引用 NULL
    int left_weight = (T->left != NULL) ? T->left->weight : 0;
    int right_weight = (T->right != NULL) ? T->right->weight : 0;
    T->weight = left_weight + right_weight;                         // 更新当前结点的权重
    return wl + wr + T->weight;
}

int main()
{
    BiTNode a = {1, NULL, NULL, 1};
    BiTNode d = {4, NULL, NULL, 4};
    BiTNode c = {3, NULL, &d, 3};
    BiTNode b = {2, &a, &c, 2};

    printf("%d", WPL(&b));
    return 0;
}

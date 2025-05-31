#include <cstdio>
#define NULL nullptr
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *left, *right;
    int weight;
} BiTNode, *BiTree;

int WeightedPathLength(BiTree T, int depth)
{
    if (T == NULL)
        return 0;
    if (T->left == NULL && T->right == NULL)
        return T->weight * depth;
    return WeightedPathLength(T->left, depth + 1) + WeightedPathLength(T->right, depth + 1);
}

int WPL(BiTree T)
{
    return WeightedPathLength(T, 0);
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

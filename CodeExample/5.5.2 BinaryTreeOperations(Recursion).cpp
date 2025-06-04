#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define MaxSize 100
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/* 1) 统计度为1的结点 */
int CountDegreeOneNodes(BiTree T)
{
    if (T == NULL) return 0;
    int current = ((T->lchild && !T->rchild) || (!T->lchild && T->rchild)) ? 1 : 0;
    return current + CountDegreeOneNodes(T->lchild) + CountDegreeOneNodes(T->rchild);
}

/* 2) 统计度为2的结点 */
int CountDegreeTwoNodes(BiTree T)
{
    if (T == NULL) return 0;
    int current = (T->lchild && T->rchild) ? 1 : 0;
    return current + CountDegreeTwoNodes(T->lchild) + CountDegreeTwoNodes(T->rchild);
}

/* 3) 统计叶子结点 */
int CountDegreeZeroNodes(BiTree T)
{
    if (T == NULL) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return CountDegreeZeroNodes(T->lchild) + CountDegreeZeroNodes(T->rchild);
}

/* 4) 计算树高度 */
int HeightOfBinaryTree(BiTree T)
{
    if (T == NULL) return 0;
    int leftH = HeightOfBinaryTree(T->lchild);
    int rightH = HeightOfBinaryTree(T->rchild);
    return (leftH > rightH ? leftH : rightH) + 1;
}

/* 5) 计算树宽度（辅助函数） */
int count[MaxSize];
int MaxWidth;

void CalculateLevelWidth(BiTree T, int level)
{
    if (T == NULL) return;
    count[level]++;
    if (count[level] > MaxWidth)
        MaxWidth = count[level];
    CalculateLevelWidth(T->lchild, level + 1);
    CalculateLevelWidth(T->rchild, level + 1);
}

int WidthOfBinaryTree(BiTree T)
{
    MaxWidth = 0;
    for (int &i: count)
        i = 0;
    CalculateLevelWidth(T, 0);
    return MaxWidth;
}

/* 6) 删除所有叶子结点 */
void RemoveLeafNodes(BiTree &T)
{
    if (T == NULL) return;
    RemoveLeafNodes(T->lchild);
    RemoveLeafNodes(T->rchild);
    if (!T->lchild && !T->rchild) {
        free(T);
        T = NULL;
    }
}

/* 7) 查找结点层次 */
int LevelOfNode(BiTree T, BiTNode *p, int currentLevel)
{
    if (T == NULL) return 0;
    if (T == p) return currentLevel;
    int leftLevel = LevelOfNode(T->lchild, p, currentLevel + 1);
    return leftLevel ? leftLevel : LevelOfNode(T->rchild, p, currentLevel + 1);
}

/* 8) 查找最大值 */
ElementType MaxValueInTree(BiTree T)
{
    if (T == NULL) return INT_MIN;
    ElementType leftMax = MaxValueInTree(T->lchild);
    ElementType rightMax = MaxValueInTree(T->rchild);
    ElementType childMax = leftMax > rightMax ? leftMax : rightMax;
    return childMax > T->data ? childMax : T->data;
}

/* 9) 交换所有子树 */
void SwapSubtree(BiTree T)
{
    if (T == NULL)
        return;
    SwapSubtree(T->lchild);
    SwapSubtree(T->rchild);
    BiTree t = T->lchild;
    T->lchild = T->rchild;
    T->rchild = t;
}

/* 10) 先序输出结点及层次 */
void PreOrderPrintWithLevel(BiTree T, int level)
{
    if (T == NULL) return;
    printf("data: %d, Level: %d\n", T->data, level);
    PreOrderPrintWithLevel(T->lchild, level + 1);
    PreOrderPrintWithLevel(T->rchild, level + 1);
}

BiTree CreateSampleBiTree()
{
    auto a = static_cast<BiTree>(malloc(sizeof(BiTree)));
    a->lchild = NULL;
    a->rchild = NULL;
    a->data = 1;
    auto d = static_cast<BiTree>(malloc(sizeof(BiTree)));
    d->lchild = NULL;
    d->rchild = NULL;
    d->data = 4;
    auto c = static_cast<BiTree>(malloc(sizeof(BiTree)));
    c->lchild = NULL;
    c->rchild = d;
    c->data = 3;
    auto root = static_cast<BiTree>(malloc(sizeof(BiTree)));
    root->lchild = a;
    root->rchild = c;
    root->data = 2;
    return root;
}


int main()
{
    BiTree root = CreateSampleBiTree();

    printf("Degree 1 nodes: %d\n", CountDegreeOneNodes(root));
    printf("Degree 2 nodes: %d\n", CountDegreeTwoNodes(root));
    printf("Degree 0 nodes: %d\n", CountDegreeZeroNodes(root));
    printf("Tree height: %d\n", HeightOfBinaryTree(root));
    printf("Tree width: %d\n", WidthOfBinaryTree(root));
    printf("Max value: %d\n", MaxValueInTree(root));

    BiTree p = root->lchild;
    printf("Node's level: %d\n", LevelOfNode(root, p, 1));

    PreOrderPrintWithLevel(root, 1);
    SwapSubtree(root);
    printf("After Swap Subtree:\n");
    PreOrderPrintWithLevel(root, 1);

    RemoveLeafNodes(root);
    printf("\nAfter removing leaves:\n");
    PreOrderPrintWithLevel(root, 1);

    return 0;
}

#include <cstdio>
#include <cstdlib>
#define NULL nullptr
typedef int ElementType;

typedef struct AVLNode {
    ElementType Data;               /* 结点数据 */
    struct AVLNode *Left, *Right;;  /* 指向左子树、右子树 */
    int Height;                     /* 树高 */
} AVLNode, *position, *AVLTree;

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree T)
{
    if (T == NULL)
        return 0;
    return GetHeight(T->Left) > GetHeight(T->Right) ? GetHeight(T->Left) + 1 : GetHeight(T->Right) + 1;
}

AVLTree SingleLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

/* 右单旋：处理右子树过高的不平衡情况 */
AVLTree SingleRightRotation(AVLTree A)
{    /* 注意：A必须有一个右子结点B */
    /* 将A与B做右单旋，更新A与B的高度，返回新的根结点B */
    AVLTree B = A->Right;  // B是A的右子结点
    A->Right = B->Left;    // 将B的左子树挂到A的右子树
    B->Left = A;           // A成为B的左子树
    /* 更新旋转后的高度 */
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1; // 先更新原根节点A的高度
    B->Height = Max(A->Height, GetHeight(B->Right)) + 1;          // 再更新新根节点B的高度
    return B;  // B成为新的根
}

/* 右-左双旋：处理右子树的左子树导致的不平衡 */
AVLTree DoubleRightLeftRotation(AVLTree A)
{    /* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 先对B和C做左单旋，C被返回 */
    A->Right = SingleLeftRotation(A->Right);  // 对右子树进行左旋处理

    /* 再对A和C做右单旋，C被返回 */
    return SingleRightRotation(A);            // 对处理后的树进行右旋
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T) { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree) malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */

    else if (X < T->Data) {
        /* 插入T的左子树 */
        T->Left = Insert(T->Left, X);
        /* 如果需要左旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
            if (X < T->Left->Data)
                T = SingleLeftRotation(T);      /* 左单旋 */
            else
                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
    } /* else if (插入左子树) 结束 */

    else if (X > T->Data) {
        /* 插入T的右子树 */
        T->Right = Insert(T->Right, X);
        /* 如果需要右旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
            if (X > T->Right->Data)
                T = SingleRightRotation(T);     /* 右单旋 */
            else
                T = DoubleRightLeftRotation(T); /* 右-左双旋 */
    } /* else if (插入右子树) 结束 */

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}

int main()
{
    int n;
    scanf("%d", &n);
    AVLTree root = NULL;
    for (int i = 0; i < n; i++) {
        int element;
        scanf("%d", &element);

        root = Insert(root, element);
    }
    if (root)
        printf("%d\n", root->Data);
    return 0;
}

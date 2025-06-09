#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* 由裁判实现，细节不表 */
bool IsBST(BinTree T);

int main()
{
    BinTree T = BuildTree();
    if (IsBST(T)) printf("Yes\n");
    else printf("No\n");

    return 0;
}

/* 你的代码将被嵌在这里 */
int pre = 0;
bool IsBST ( BinTree T )
{
    /* 指针 bt 指向二叉树的结构体，i 是当前访问的下标 */
    if (T == NULL)
        return true;           // 当前结点为空，或者结点遍历结束
    if (!IsBST(T->Left))       // 递归调用左子树
        return false;          // 左子树不符合定义
    if (pre > T->Data)         // 访问当前结点
        return false;          // 前驱大于当前结点，不符合定义
    pre = T->Data;             // 更新 pre
    if (!IsBST(T->Right))      // 递归调用右子树
        return false;          // 右子树不符合定义
    return true;               // 根下标为 i 的子树符合定义
}
#include <cstdio>
#define MAX_SIZE 100

typedef struct {              // MAX_SIZE 为已定义常量
    int SqBiTNode[MAX_SIZE];  // 保存二叉树结点值的数组
    int ElemNum;              // 实际占用的数组元素个数 SqBiTree;
} SqBiTNode;

int pre = 0;                            //全局变量 pre 保存中序前驱的权值 (初值 0)

bool JudgeBST(SqBiTNode *bt, int i, int n)
{
    /* 指针 bt 指向二叉树的结构体，i 是当前访问的下标 */
    if (bt->SqBiTNode[i] == -1 || i >= n)
        return true;                    // 当前结点为空，或者结点遍历结束
    if (!JudgeBST(bt, 2 * i + 1, n))  // 递归调用左子树
        return false;                   // 左子树不符合定义
    if (pre > bt->SqBiTNode[i])         // 访问当前结点
        return false;                   // 前驱大于当前结点，不符合定义
    pre = bt->SqBiTNode[i];             // 更新 pre
    if (!JudgeBST(bt, 2 * i + 2, n))  // 递归调用右子树
        return false;                   // 右子树不符合定义
    return true;                        // 根下标为 i 的子树符合定义
}

int main()
{
    SqBiTNode T1 = {{40, 25, 60, -1, 30, -1, 80, -1, -1, 27}, 10};
    printf("%d\n", JudgeBST(&T1, 0, T1.ElemNum));
    SqBiTNode T2 = {{40, 50, 60, -1, 30, -1, -1, -1, -1, -1, 35}, 11};
    pre = 0;        // 初始化全局变量，避免之前的影响
    printf("%d\n", JudgeBST(&T2, 0, T2.ElemNum));
    SqBiTNode T3 = {{50, 30, 70, -1, -1, 40, 80}, 7};
    pre = 0;
    printf("%d\n", JudgeBST(&T3, 0, T3.ElemNum));

    return 0;
}

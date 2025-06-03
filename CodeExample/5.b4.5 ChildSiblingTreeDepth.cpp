#include <cstdio>
#define NULL nullptr
typedef int ElementType;

typedef struct CSNode {
    ElementType data;                           // 数据域
    struct CSNode *firstchild, *nextsibling;    // 第一个孩子指针和右兄弟指针
} CSNode, *CSTree;

int ChildSiblingTreeDepth(CSTree T)
{
    if (T == NULL)
        return 0;
    int ctree = ChildSiblingTreeDepth(T->firstchild);
    int stree = ChildSiblingTreeDepth(T->nextsibling);
    return ctree + 1 >= stree ? ctree + 1 : stree;
}

int main()
{
    // 构建节点
    CSNode node_d = {4, NULL, NULL};
    CSNode node_c = {3, NULL, NULL};
    CSNode node_b = {2, &node_c, &node_d};
    CSNode node_a = {1, &node_b, NULL};

    // 计算并打印结果
    printf("The Depth of Tree:%d", ChildSiblingTreeDepth(&node_a));
    return 0;
}

#include <cstdio>
#define NULL nullptr
typedef int ElementType;

typedef struct CSNode {
    ElementType data;                           // 数据域
    struct CSNode *firstchild, *nextsibling;    // 第一个孩子指针和右兄弟指针
} CSNode, *CSTree;

int count = 0;

void CountLeavesChildSiblingForest(CSTree T)
{
    if (T) {
        CountLeavesChildSiblingForest(T->firstchild);
        if (T->firstchild == NULL)
            count++;
        CountLeavesChildSiblingForest(T->nextsibling);
    }
}

int main()
{
    // 构建节点
    CSNode node_d = {4, NULL, NULL};
    CSNode node_c = {3, NULL, NULL};
    CSNode node_b = {2, &node_c, &node_d};
    CSNode node_a = {1, &node_b, NULL};
    CountLeavesChildSiblingForest(&node_a);
    // 计算并打印结果
    printf("The number of Forest's Leaves:%d", count);
    return 0;
}

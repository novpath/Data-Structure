#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define INF 0x3f3f3f3f

typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *lchild;
    BiTNode *rchild;
} BiTNode, *BiTree;

BiTree BuildTree();

void FindMinMax(BiTree T, int &min, int &max)
{
    if (T == NULL)
        return;
    BiTNode *p = T;
    while (p->lchild != NULL) {
        p = p->lchild;
    }
    min = p->data;
    p = T;
    while (p->rchild != NULL) {
        p = p->rchild;
    }
    max = p->data;
}

int main()
{
    BiTree T = BuildTree();
    int min = INF, max = -INF;
    FindMinMax(T, min, max);
    printf("Max = %d, Min = %d", max, min);
    free(T);
    return 0;
}

BiTree BuildTree()
{
    int nodeCount;
    printf("Please input the number of nodes(including empty nodes):");
    scanf("%d", &nodeCount);
    // 创建存储节点值的数组
    int *values = (int *) malloc(nodeCount * sizeof(int));
    printf("Please input the layer ordered sequence (Empty nodes input -1):\n");
    for (int i = 0; i < nodeCount; i++) {
        scanf("%d", &values[i]);
    }

    // 创建节点指针数组作为队列
    BiTree *queue = (BiTree *) malloc(nodeCount * sizeof(BiTree));
    int front = 0, rear = 0;
    // 创建根节点
    BiTree root = NULL;
    if (values[0] != -1) {
        root = (BiTree) malloc(sizeof(struct BiTNode));
        root->data = values[0];
        root->lchild = root->rchild = NULL;
        queue[rear++] = root;
    }

    int index = 1;  // 当前处理的节点值索引
    while (front < rear && index < nodeCount) {
        BiTree currentNode = queue[front++];
        // 处理左子树
        if (index < nodeCount && values[index] != -1) {
            BiTree leftNode = (BiTree) malloc(sizeof(struct BiTNode));
            leftNode->data = values[index];
            leftNode->lchild = leftNode->rchild = NULL;
            currentNode->lchild = leftNode;
            queue[rear++] = leftNode;
        }
        index++;

        // 处理右子树
        if (index < nodeCount && values[index] != -1) {
            BiTree rightNode = (BiTree) malloc(sizeof(struct BiTNode));
            rightNode->data = values[index];
            rightNode->lchild = rightNode->rchild = NULL;
            currentNode->rchild = rightNode;
            queue[rear++] = rightNode;
        }
        index++;
    }

    // 释放临时数组
    free(values);
    free(queue);

    return root;
}


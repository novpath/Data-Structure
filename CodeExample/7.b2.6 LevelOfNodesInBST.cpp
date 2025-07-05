#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define INF 0x3f3f3f3f
#define MaxNodesNum 100

typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    BiTNode *lchild;
    BiTNode *rchild;
} BiTNode, *BiTree;

BiTree BuildTree();

int LevelOfNodes(BiTree T, BiTree p)
{
    if (T == NULL || p == NULL)
        return 0;
    int level = 1;
    while (T->data != p->data) {
        if (p->data < T->data)
            T = T->lchild;
        else
            T = T->rchild;
        level++;
    }
    return level;
}

int main()
{
    BiTree T = BuildTree();
    printf("%d\n", LevelOfNodes(T, T->lchild->rchild));
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


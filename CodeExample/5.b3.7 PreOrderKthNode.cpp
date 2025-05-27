#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree PreOrderKthNodeCore(BiTree T, int k, int *pos)
{
    if (T == NULL) return NULL;
    if (*pos == k) return T;                           // 当前节点为第 k 个
    (*pos)++;                                          // 递增位置计数器
    BiTree left = PreOrderKthNodeCore(T->lchild, k, pos);
    if (left) return left;                             // 左子树找到则返回
    return PreOrderKthNodeCore(T->rchild, k, pos);     // 返回右子树结果，可能为 NULL
}

BiTree PreOrderKthNode(BiTree T, int k)
{
    int pos = 1;                              // 每次调用自动初始化
    return PreOrderKthNodeCore(T, k, &pos);
}


BiTree CreateTree();
void PrintTree();

int main()
{
    PrintTree();
    BiTree root = CreateTree();
    printf("PreOrder:");
    for (int i = 1; i <= 8; i++) {
        BiTree p = PreOrderKthNode(root, i);
        if (p)
            printf("%d", p->data);
        else
            printf("#");
    }

    return 0;
}

// 创建三层满二叉树
BiTree CreateTree()
{
    BiTNode *nodes[7];
    for (int i = 0; i < 7; i++) {
        nodes[i] = (BiTNode *) malloc(sizeof(BiTNode));
        nodes[i]->data = i + 1;
        nodes[i]->lchild = NULL;
        nodes[i]->rchild = NULL;
    }
    nodes[0]->lchild = nodes[1];
    nodes[0]->rchild = nodes[2];
    nodes[1]->lchild = nodes[3];
    nodes[1]->rchild = nodes[4];
    nodes[2]->lchild = nodes[5];
    nodes[2]->rchild = nodes[6];
    return nodes[0];
}

void PrintTree()
{
    // 定义每行的宽度和行数
    const int width = 15; // 足够容纳最底层的节点
    const int rows = 5;
    char output[rows][width];
    // 初始化输出数组为空格
    for (int i = 0; i < rows; i++) {
        memset(output[i], ' ', width);
        output[i][width - 1] = '\0'; // 字符串终止符
    }
    // 填充节点数据（行0,2,4）
    output[0][7] = '1';          // 层0
    output[2][3] = '2';          // 层1左
    output[2][11] = '3';         // 层1右
    output[4][1] = '4';          // 层2左左
    output[4][5] = '5';          // 层2左右
    output[4][9] = '6';          // 层2右左
    output[4][13] = '7';         // 层2右右
    // 填充连接符（行1,3）
    output[1][5] = '/';
    output[1][9] = '\\'; // 层0的连接符
    output[3][2] = '/';
    output[3][4] = '\\'; // 层1的左连接符
    output[3][10] = '/';
    output[3][12] = '\\'; // 层1的右连接符

    // 打印所有行
    for (int i = 0; i < rows; i++) {
        printf("%s\n", output[i]);
    }
}

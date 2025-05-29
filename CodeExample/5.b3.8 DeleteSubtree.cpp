#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MaxSize 100

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqQueue {
    BiTree data[MaxSize];
    int front, rear;;
} SqQueue;

BiTree CreateTree();
void PrintTree();
bool EnQueue(SqQueue &Q, BiTree x);
bool DeQueue(SqQueue &Q, BiTree &x);

void DeleteSubtree(BiTree &T)
{
    if (T == NULL)
        return;
    DeleteSubtree(T->lchild);   // 删除左子树
    DeleteSubtree(T->rchild);   // 删除右子树
    free(T);                        // 删除根结点
    T = NULL;                       // 置空 T 指针
}

void DeleteXSubtree(BiTree &T, const int x)
{
    SqQueue Q;
    if (T == NULL)
        return;
    if (T->data == x) {
        DeleteSubtree(T);
        return;
    }
    Q.front = Q.rear = 0;
    EnQueue(Q, T);
    while (Q.front != Q.rear) {
        BiTree p;
        DeQueue(Q, p);
        if (p->lchild) {                       // 若左子女非空
            if (p->lchild->data == x) {        // 左子树符合则删除左子树
                DeleteSubtree(p->lchild);
                p->lchild = NULL;              // 父结点的左子女置空
            } else {
                EnQueue(Q, p->lchild);     // 左子女入队
            }
        }
        if (p->rchild) {                       // 若右子女非空
            if (p->rchild->data == x) {        // 右子女符合则删除右子树
                DeleteSubtree(p->rchild);
                p->rchild = NULL;              // 父结点的右子女置空
            } else {
                EnQueue(Q, p->rchild);     // 右子女入队
            }
        }
    }
}

int main()
{
    PrintTree();
    BiTree root = CreateTree();
    DeleteXSubtree(root, 3);

    return 0;
}

// 创建三层满二叉树
BiTree CreateTree()
{
    BiTNode *nodes[7];
    for (int i = 0; i < 7; i++) {
        nodes[i] = static_cast<BiTree>(malloc(sizeof(BiTNode)));
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
    constexpr int width = 15; // 足够容纳最底层的节点
    constexpr int rows = 5;
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

bool EnQueue(SqQueue &Q, BiTree x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, BiTree &x)
{
    if (Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

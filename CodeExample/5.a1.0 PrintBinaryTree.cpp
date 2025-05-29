#include <cstdio>
#include <cstdlib>
#include <cstring>
#define NULL nullptr
#define MaxSize 100
#define TREE_HEIGHT 4
#define PRINT_WIDTH 63

typedef struct BiTNode {
    char data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqQueue {
    BiTree data[MaxSize];
    int front, rear;
} SqQueue;

/* 打印二叉树，空结点用'#'表示 */
void PrintBinaryTree(BiTree root);
void InitQueue(SqQueue &Q);
int IsQueueEmpty(const SqQueue &Q);
int EnQueue(SqQueue &Q, BiTree elem);
int DeQueue(SqQueue &Q, BiTree &elem);
/* 创建二叉树，以逗号分隔,支持单个数字及符号的输入 */
BiTree CreateBiTree(const char input[]);

void DeleteSubtree(BiTree &T)
{
    if (T) {
        DeleteSubtree(T->lchild);   // 删除左子树
        DeleteSubtree(T->rchild);   // 删除右子树
        free(T);                        // 删除根结点
        T = NULL;                       // 置空 T 指针
    }
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
    char str[100];
    scanf("%s", str);
    BiTree root = CreateBiTree(str);
    PrintBinaryTree(root);
    printf("After deleting:\n");
    DeleteXSubtree(root, '1');
    PrintBinaryTree(root);

    return 0;
}

void PrintBinaryTree(BiTree root)
{
    char canvas[2 * TREE_HEIGHT - 1][PRINT_WIDTH + 1];
    for (auto &canva: canvas) {
        memset(canva, ' ', PRINT_WIDTH);
        canva[PRINT_WIDTH] = '\0';
    }

    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, root);

    int level = 0;

    // 节点位置记录
    while (!IsQueueEmpty(Q) && level < TREE_HEIGHT) {
        int level_size = 1 << level;
        int spacing = PRINT_WIDTH / (level_size + 1);

        for (int i = 0; i < level_size; i++) {
            BiTree node;
            if (!DeQueue(Q, node)) break;

            int pos = spacing * (i + 1) - 1;

            if (node) {
                canvas[2 * level][pos - 1] = node->data;
                EnQueue(Q, node->lchild);
                EnQueue(Q, node->rchild);
            } else {
                canvas[2 * level][pos] = '#';
                EnQueue(Q, NULL);
                EnQueue(Q, NULL);
            }
        }
        level++;
    }

    // 打印结果
    for (auto &canva: canvas)
        printf("%s\n", canva);
    printf("\n");
}

// 队列操作函数
void InitQueue(SqQueue &Q)
{
    Q.front = Q.rear = 0;
}

int IsQueueEmpty(const SqQueue &Q)
{
    return Q.front == Q.rear;
}

int EnQueue(SqQueue &Q, BiTree elem)
{
    if ((Q.rear + 1) % MaxSize == Q.front) return 0;
    Q.data[Q.rear] = elem;
    Q.rear = (Q.rear + 1) % MaxSize;
    return 1;
}

int DeQueue(SqQueue &Q, BiTree &elem)
{
    if (IsQueueEmpty(Q)) return 0;
    elem = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return 1;
}

BiTree CreateBiTree(const char input[])
{
    if (input[0] == '\0')
        return NULL;
    // 创建根节点
    auto root = static_cast<BiTree>(malloc(sizeof(BiTNode)));
    root->data = input[0];
    root->lchild = root->rchild = NULL;

    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, root);

    int index = 1;

    // 层序构建二叉树
    while (input[index] != '\0') {
        BiTree temp;
        DeQueue(Q, temp);
        // 处理左子树
        if (input[index] == ',')
            index++;

        temp->lchild = static_cast<BiTree>(malloc(sizeof(BiTNode)));
        temp->lchild->data = input[index];
        temp->lchild->lchild = temp->lchild->rchild = NULL;
        EnQueue(Q, temp->lchild);
        index++;
        // 处理右子树
        if (input[index] == ',')
            index++;
        temp->rchild = static_cast<BiTree>(malloc(sizeof(BiTNode)));
        temp->rchild->data = input[index];
        temp->rchild->lchild = temp->rchild->rchild = NULL;
        EnQueue(Q, temp->rchild);
        index++;
    }
    return root;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
/* ↓--------------- 二叉树初始化部分 ----------------↓ */
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

void PrintBinaryTree(BiTree root);
void InitQueue(SqQueue &Q);
int IsQueueEmpty(const SqQueue &Q);
int EnQueue(SqQueue &Q, BiTree elem);
int DeQueue(SqQueue &Q, BiTree &elem);
BiTree CreateBiTree(const char input[]);
/* ↑--------------- 二叉树初始化部分 ----------------↑ */
typedef char ElementType;

typedef struct SqStack {
    BiTree data[MaxSize];
    int top;
} SqStack;

void StackInit(SqStack &S)
{
    S.top = -1;
}

bool IsStackEmpty(const SqStack &S)
{
    return S.top == -1;
}

bool Push(SqStack &S, BiTree elem)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = elem;
    return true;
}

bool Pop(SqStack &S, BiTree &elem)
{
    if (S.top == -1)
        return false;
    elem = S.data[S.top--];
    return true;
}

void AncestorsOfXNode(SqStack &S, BiTree root, ElementType x)
{
    if (root == NULL)
        return;
    Push(S, root);
    AncestorsOfXNode(S, root->lchild, x);
    AncestorsOfXNode(S, root->rchild, x);
    BiTree tmp;
    Pop(S, tmp);
    if (tmp->data == x) {
        while (!IsStackEmpty(S)) {
            Pop(S, tmp);
            printf("%c ", tmp->data);
        }
    }
}

int main()
{
    SqStack S;
    StackInit(S);
    char str[100];
    /* 4 层满二叉树：1,2,3,4,5,6,7,8,9,A,B,C,D,E,F */
    scanf("%s", str);
    getchar();
    char ch;
    scanf("%c", &ch);
    BiTree root = CreateBiTree(str);
    PrintBinaryTree(root);
    AncestorsOfXNode(S, root, ch);

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

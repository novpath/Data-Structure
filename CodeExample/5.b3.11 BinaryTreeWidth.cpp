#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef char ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/* ↓--------------- 二叉树初始化部分 ----------------↓ */
#define NULL nullptr
#define MaxSize 100
#define TREE_HEIGHT 4
#define PRINT_WIDTH 63

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
int BinaryTreeWidth(BiTree T)
{
    if (T == NULL)
        return 0;
    int width = 0, cnt = 0;
    SqQueue QA, QB;
    InitQueue(QA);
    InitQueue(QB);
    EnQueue(QA, T);
    SqQueue *ta = &QA;
    SqQueue *tb = &QB;
    while (!IsQueueEmpty(*ta) || !IsQueueEmpty(*tb)) {
        BiTree tmp;
        DeQueue(*ta, tmp);
        cnt++;
        if (tmp->lchild)
            EnQueue(*tb, tmp->lchild);
        if (tmp->rchild)
            EnQueue(*tb, tmp->rchild);
        if (IsQueueEmpty(*ta)) {
            SqQueue *t = ta;
            ta = tb;
            tb = t;
            width = width >= cnt ? width : cnt;
            cnt = 0;
        }
    }
    return width;
}

int main()
{
    char str[100];
    /* 4 层满二叉树：1,2,3,4,5,6,7,8,9,A,B,C,D,E,F */
    scanf("%s", str);
    BiTree root = CreateBiTree(str);
    PrintBinaryTree(root);
    printf("%d\n", BinaryTreeWidth(root));

    return 0;
}

BiTree CreateBiTree(const char input[])
{
    // 分割输入字符串为逗号分隔的数组
    char elements[MaxSize][2]; // 存储每个分割的元素
    int elem_count = 0;

    const char *delim = ",";
    char input_copy[MaxSize];
    strncpy(input_copy, input, MaxSize); // 复制输入字符串

    char *token = strtok(input_copy, delim);
    while (token != nullptr && elem_count < MaxSize) {
        strncpy(elements[elem_count], token, 2); // 避免溢出
        elem_count++;
        token = strtok(nullptr, delim);
    }

    if (elem_count == 0 || elements[0][0] == '#')
        return nullptr;

    // 创建根节点
    auto root = static_cast<BiTree>(malloc(sizeof(BiTNode)));
    root->data = elements[0][0];
    root->lchild = root->rchild = nullptr;

    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, root);

    int index = 1; // 当前处理的元素索引

    while (!IsQueueEmpty(Q) && index < elem_count) {
        BiTree parent;
        DeQueue(Q, parent);

        // 处理左子节点
        if (index < elem_count && elements[index][0] != '#') {
            auto left = static_cast<BiTree>(malloc(sizeof(BiTNode)));
            left->data = elements[index][0];
            left->lchild = left->rchild = nullptr;
            parent->lchild = left;
            EnQueue(Q, left);
        }
        index++;

        // 处理右子节点
        if (index < elem_count && elements[index][0] != '#') {
            auto right = static_cast<BiTree>(malloc(sizeof(BiTNode)));
            right->data = elements[index][0];
            right->lchild = right->rchild = nullptr;
            parent->rchild = right;
            EnQueue(Q, right);
        }
        index++;
    }

    return root;
}

void PrintBinaryTree(BiTree root)
{
    char canvas[2 * TREE_HEIGHT - 1][PRINT_WIDTH + 1];
    for (auto &row: canvas) {
        memset(row, ' ', PRINT_WIDTH);
        row[PRINT_WIDTH] = '\0';
    }

    BiTree current_level[1 << TREE_HEIGHT];             // 当前层节点数组
    int current_size = 0;
    current_level[current_size++] = root;               // 初始为根节点

    for (int level = 0; level < TREE_HEIGHT; ++level) {
        int level_nodes = 1 << level;                   // 当前层应有的节点数
        int spacing = PRINT_WIDTH / (level_nodes + 1);
        bool has_non_null = false;

        for (int i = 0; i < level_nodes; ++i) {
            BiTree node = (i < current_size) ? current_level[i] : nullptr;
            int pos = spacing * (i + 1) - 1;

            if (node) {
                canvas[2 * level][pos] = node->data;
                has_non_null = true;
            } else {
                canvas[2 * level][pos] = '#';        // 空节点显示为#
            }
        }

        if (!has_non_null) break;                    // 当前层全为空，无需继续
        BiTree next_level[1 << (TREE_HEIGHT + 1)];   // 生成下一层节点数组
        int next_size = 0;
        for (int i = 0; i < current_size; ++i) {
            if (BiTree node = current_level[i]) {
                next_level[next_size++] = node->lchild;
                next_level[next_size++] = node->rchild;
            } else {
                next_level[next_size++] = nullptr;
                next_level[next_size++] = nullptr;
            }
        }

        current_size = next_size;                                       // 更新当前层信息
        memcpy(current_level, next_level, sizeof(BiTree) * next_size);
    }

    for (auto &canva: canvas)   // 打印画布
        printf("%s\n", canva);
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100
#define TREE_HEIGHT 4
#define PRINT_WIDTH 63

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqQueue {
    BiTree data[MaxSize];
    int front, rear;
} SqQueue;

// 队列操作函数
void InitQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
}

int IsQueueEmpty(SqQueue *Q)
{
    return Q->front == Q->rear;
}

int EnQueue(SqQueue *Q, BiTree elem)
{
    if ((Q->rear + 1) % MaxSize == Q->front) return 0;
    Q->data[Q->rear] = elem;
    Q->rear = (Q->rear + 1) % MaxSize;
    return 1;
}

int DeQueue(SqQueue *Q, BiTree *elem)
{
    if (IsQueueEmpty(Q)) return 0;
    *elem = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return 1;
}

// 修正后的打印函数
void PrintBinaryTree(BiTree root)
{
    if (!root) return;

    char canvas[2 * TREE_HEIGHT - 1][PRINT_WIDTH + 1];
    for (int i = 0; i < 2 * TREE_HEIGHT - 1; i++) {
        memset(canvas[i], ' ', PRINT_WIDTH);
        canvas[i][PRINT_WIDTH] = '\0';
    }

    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, root);

    int level_pos[TREE_HEIGHT][1 << TREE_HEIGHT] = {0};
    int level = 0;

    // 节点位置记录
    while (!IsQueueEmpty(&Q) && level < TREE_HEIGHT) {
        int level_size = 1 << level;
        int spacing = PRINT_WIDTH / (level_size + 1);

        for (int i = 0; i < level_size; i++) {
            BiTree node;
            if (!DeQueue(&Q, &node)) break;

            int pos = spacing * (i + 1) - 1;
            level_pos[level][i] = pos;

            if (node) {
                char str[3];
                sprintf(str, "%02d", node->data);
                memcpy(&canvas[2 * level][pos - 1], str, 2);
                EnQueue(&Q, node->lchild);
                EnQueue(&Q, node->rchild);
            } else {
                canvas[2 * level][pos] = '#';
                EnQueue(&Q, NULL);
                EnQueue(&Q, NULL);
            }
        }
        level++;
    }

    // 修正后的连接线绘制逻辑
    for (level = 0; level < TREE_HEIGHT - 1; level++) {
        int line_row = 2 * level + 1;
        int nodes = 1 << level;

        for (int i = 0; i < nodes; i++) {
            int parent_pos = level_pos[level][i];
            int left_child_pos = level_pos[level + 1][2 * i];
            int right_child_pos = level_pos[level + 1][2 * i + 1];

            // 绘制左斜线（单线）
            if (left_child_pos != 0) {
                int steps = (parent_pos - left_child_pos) / 2;
                for (int j = 1; j <= steps; j++) {
                    int line_col = parent_pos - j;
                    if (line_col >= 0 && line_col < PRINT_WIDTH) {
                        canvas[line_row][line_col] = '/';
                    }
                }
            }

            // 绘制右斜线（单线）
            if (right_child_pos != 0) {
                int steps = (right_child_pos - parent_pos) / 2;
                for (int j = 1; j <= steps; j++) {
                    int line_col = parent_pos + j;
                    if (line_col < PRINT_WIDTH) {
                        canvas[line_row][line_col] = '\\';
                    }
                }
            }
        }
    }

    // 打印结果
    for (int i = 0; i < 2 * TREE_HEIGHT - 1; i++) {
        printf("%s\n", canvas[i]);
    }
}

int main()
{
    // 四层满二叉树结构
    BiTNode n8 = {8}, n9 = {9}, n10 = {10}, n11 = {11};
    BiTNode n12 = {12}, n13 = {13}, n14 = {14}, n15 = {15};
    BiTNode n4 = {4, &n8, &n9}, n5 = {5, &n10, &n11};
    BiTNode n6 = {6, &n12, &n13}, n7 = {7, &n14, &n15};
    BiTNode n2 = {2, &n4, &n5}, n3 = {3, &n6, &n7};
    BiTNode root = {1, &n2, &n3};

    PrintBinaryTree(&n4);
    return 0;
}

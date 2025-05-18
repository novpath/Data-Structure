#include <stdio.h>
#define MaxSize 1000            // 定义队列中元素的最大个数
typedef  int ElementType;
typedef struct {
    ElementType data[MaxSize];  // 用静态数组存放队列元素
    int front, rear;            // 队首指针和队尾指针
} SqQueue;

bool EnQueue(SqQueue &Q, ElementType x)
{
    if ((Q.rear + 1) % MaxSize == Q.front)   // 队满则报错
        return false;
    Q.data[Q.rear] = x;                      // 将 x 插入队尾
    Q.rear = (Q.rear + 1) % MaxSize;         // 队尾指针加 1 取模
    return true;
}

ElementType DeQueue(SqQueue &Q)   // 只能让队头元素出队
{
    if (Q.rear == Q.front)                 // 队空则报错
        return false;
    ElementType x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;     // 队首指针加 1 取模
    return x;
}

int main()
{
    SqQueue QA, QB;
    QA.rear = QA.front = 0;
    QB.rear = QB.front = 0;;
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x % 2 == 1)
            EnQueue(QA, x);
        else
            EnQueue(QB, x);
    }
    for (int i = 0; i < n; i++) {
        if (QA.front != QA.rear && (QB.front == QB.rear || (i + 1) % 3 != 0))
            printf("%d", DeQueue(QA));
        else if (QB.rear != QB.front)
            printf("%d", DeQueue(QB));
        if (i != n - 1)
            printf(" ");
    }
    return 0;
}
#include <stdio.h>
#define MaxSize 50              // 定义队列中元素的最大个数

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize];  // 用静态数组存放队列元素
    int front, rear;            // 队首指针和队尾指针
    int tag;                    // 0 表示最近出队，1 表示最近入队。
} SqQueue;

bool EnQueue(SqQueue &Q, ElementType x)
{
    if (Q.front == Q.rear && Q.tag == 1)     // 队满
        return false;
    Q.data[Q.rear] = x;                      // 将 x 插入队尾
    Q.rear = (Q.rear + 1) % MaxSize;         // 队尾指针加 1 取模
    Q.tag = 1;                               // 最近操作为入队，置 tag 为 1
    return true;
}

bool DeQueue(SqQueue &Q, ElementType &x)
{
    if (Q.front == Q.rear && Q.tag == 0)     // 队空
        return false;
    x = Q.data[Q.front];                     // 将队头元素的值赋予 x
    Q.front = (Q.front + 1) % MaxSize;       // 队头指针加 1 取模
    Q.tag = 0;                               // 最近操作为出队，置 tag 为 0
    return true;
}

int main()
{
	SqQueue Q;
	Q.front = 0;
	Q.rear = 0;
	
	int x = 0;
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	DeQueue(Q, x);
	printf("%d\n", x);
	int length = (Q.rear - Q.front + MaxSize) % MaxSize;
	for (int i = 0; i < length; i++) {
		printf("%d ", Q.data[(Q.front + i) % MaxSize]);
	}

    return 0;
}


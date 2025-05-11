#include <stdio.h>
#define MaxSize 50              // 定义队列中元素的最大个数

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize];  // 用静态数组存放队列元素
    int front, rear;            // 队首指针和队尾指针
} SqQueue;

typedef struct {
    ElementType data[MaxSize]; // 静态数组存放栈中元素
    int top;                   // 栈顶指针
} SqStack;

void InitQueue(SqQueue &Q)
{
    Q.rear = Q.front = 0;    // 初始化队首、队尾指针
}

bool QueueEmpty(SqQueue Q) 
{
    if (Q.rear == Q.front)    // 队空条件
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q, ElementType x) 
{
    if ((Q.rear + 1) % MaxSize == Q.front)   // 队满则报错
        return false;
    Q.data[Q.rear] = x;                      // 将 x 插入队尾
    Q.rear = (Q.rear + 1) % MaxSize;         // 队尾指针加 1 取模
    return true;
}

bool DeQueue(SqQueue &Q, ElementType &x)   // 只能让队头元素出队
{
    if (Q.rear == Q.front)                 // 队空则报错
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;     // 队首指针加 1 取模
    return true;
}

void InitStack(SqStack &S)
{
    S.top = -1;            // 初始化栈顶指针
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // 栈空
        return true;
    else                   // 不空
        return false;
}

bool Push(SqStack &S, ElementType x)
{
    if (S.top == MaxSize - 1)     // 栈满，报错
        return false;
    S.data[++S.top] = x;          // 指针先加 1，再入栈
    return true;
}

bool Pop(SqStack &S, ElementType &x)
{
    if (S.top == -1)        // 栈空，报错
        return false;
    x = S.data[S.top--];    // 先出栈，指针再减 1
    return true;
}

void ReverseQueue(SqQueue &Q, SqStack &S)
{
    ElementType x;
    while (!QueueEmpty(Q)) {  // 出队直到队列空 
        DeQueue(Q, x);	      // 出队 
        Push(S, x);			  // 入栈 
    }
    while (!StackEmpty(S)) {  // 出栈直到栈空 
        Pop(S, x);			  // 出栈 
        EnQueue(Q, x);		  // 入队 
    }
}

void PrintQueue(SqQueue Q) {
    int i = Q.front;
    while (i != Q.rear) {
        printf("%d ", Q.data[i]);
        i = (i + 1) % MaxSize;
    }
}

int main()
{
	SqQueue Q;
	SqStack S;
	InitQueue(Q);
	InitStack(S);
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	PrintQueue(Q);
	printf("\n");
	ReverseQueue(Q, S);
	PrintQueue(Q);

    return 0;
}


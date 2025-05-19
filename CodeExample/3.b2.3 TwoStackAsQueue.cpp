#include <stdio.h>
#define MaxSize 5              // 定义队列中元素的最大个数

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize]; // 静态数组存放栈中元素
    int top;                   // 栈顶指针
} SqStack;

void InitStack(SqStack &S); 
bool StackEmpty(SqStack S);
bool StackOverflow(SqStack S);
bool Push(SqStack &S, ElementType x);
bool Pop(SqStack &S, ElementType &x);

bool Enqueue(SqStack &S1, SqStack &S2, ElementType x)
{
    if (!StackOverflow(S1)) {
        Push(S1, x);
        return true;
    } else {
        if (StackEmpty(S2)) {
            while (!StackEmpty(S1)) {
                ElementType e;
                Pop(S1, e);
                Push(S2, e);
            }
            Push(S1, x);
            return true;
        } else {
            printf("Queue is Full!\n");
            return false;
        }
    }
}

bool Dequeue(SqStack &S1, SqStack &S2, ElementType &x)
{
    if (!StackEmpty(S2)) {
        Pop(S2, x);
    } else {
        if (StackEmpty(S1)) {
            printf("Queue is Empty!\n");
            return false;
        } else {
            while (!StackEmpty(S1)) {
                Pop(S1, x);
                Push(S2, x);
            }
            Pop(S2, x);
        }
    }
    return true;
}

bool QueueEmpty(SqStack &S1, SqStack &S2)
{
    if (StackEmpty(S1) && StackEmpty(S2))
        return true;
    else
        return false;
}

int main()
{
	int x;
	SqStack S1, S2;
	InitStack(S1);
	InitStack(S2);
	printf("%d\n", QueueEmpty(S1, S2));
	
	int cal = 0;
	while (cal != 9999) {
		printf("Press 1 to Enqueue, Press 0 to Dequeue, Press 9999 to PrintQueue\n");
		scanf("%d", &cal);
		switch (cal) {
			case 0: {
				Dequeue(S1, S2, x);
				break;
			}
			case 1: {
				printf("Plese Input x:");
				scanf("%d", &x);
				Enqueue(S1, S2, x);
				break;
			}
			case 9999:{
				break;
			}
		}
	}
	
	while (!QueueEmpty(S1, S2)) {
		Dequeue(S1, S2, x);
		printf("%d ", x);
	}

    return 0;
}

void InitStack(SqStack &S)
{
    S.top = -1;                // 初始化栈顶指针
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // 栈空
        return true;
    else                   // 不空
        return false;
}

bool StackOverflow(SqStack S)
{
    if (S.top == MaxSize - 1) // 栈满
        return true;
    else                      // 不满
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


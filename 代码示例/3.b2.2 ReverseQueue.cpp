#include <stdio.h>
#define MaxSize 50              // ���������Ԫ�ص�������

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize];  // �þ�̬�����Ŷ���Ԫ��
    int front, rear;            // ����ָ��Ͷ�βָ��
} SqQueue;

typedef struct {
    ElementType data[MaxSize]; // ��̬������ջ��Ԫ��
    int top;                   // ջ��ָ��
} SqStack;

void InitQueue(SqQueue &Q)
{
    Q.rear = Q.front = 0;    // ��ʼ�����ס���βָ��
}

bool QueueEmpty(SqQueue Q) 
{
    if (Q.rear == Q.front)    // �ӿ�����
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q, ElementType x) 
{
    if ((Q.rear + 1) % MaxSize == Q.front)   // �����򱨴�
        return false;
    Q.data[Q.rear] = x;                      // �� x �����β
    Q.rear = (Q.rear + 1) % MaxSize;         // ��βָ��� 1 ȡģ
    return true;
}

bool DeQueue(SqQueue &Q, ElementType &x)   // ֻ���ö�ͷԪ�س���
{
    if (Q.rear == Q.front)                 // �ӿ��򱨴�
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;     // ����ָ��� 1 ȡģ
    return true;
}

void InitStack(SqStack &S)
{
    S.top = -1;            // ��ʼ��ջ��ָ��
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // ջ��
        return true;
    else                   // ����
        return false;
}

bool Push(SqStack &S, ElementType x)
{
    if (S.top == MaxSize - 1)     // ջ��������
        return false;
    S.data[++S.top] = x;          // ָ���ȼ� 1������ջ
    return true;
}

bool Pop(SqStack &S, ElementType &x)
{
    if (S.top == -1)        // ջ�գ�����
        return false;
    x = S.data[S.top--];    // �ȳ�ջ��ָ���ټ� 1
    return true;
}

void ReverseQueue(SqQueue &Q, SqStack &S)
{
    ElementType x;
    while (!QueueEmpty(Q)) {  // ����ֱ�����п� 
        DeQueue(Q, x);	      // ���� 
        Push(S, x);			  // ��ջ 
    }
    while (!StackEmpty(S)) {  // ��ջֱ��ջ�� 
        Pop(S, x);			  // ��ջ 
        EnQueue(Q, x);		  // ��� 
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


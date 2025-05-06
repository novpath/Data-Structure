#include <stdio.h>
#define MaxSize 5              // ���������Ԫ�ص�������

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize]; // ��̬������ջ��Ԫ��
    int top;                   // ջ��ָ��
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
                Pop(S1, x);
                Push(S2, x);
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
    S.top = -1;                // ��ʼ��ջ��ָ��
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // ջ��
        return true;
    else                   // ����
        return false;
}

bool StackOverflow(SqStack S)
{
    if (S.top == MaxSize - 1) // ջ��
        return true;
    else                      // ����
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


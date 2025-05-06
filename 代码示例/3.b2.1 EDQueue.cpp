#include <stdio.h>
#define MaxSize 50              // ���������Ԫ�ص�������

typedef int ElementType;

typedef struct {
    ElementType data[MaxSize];  // �þ�̬�����Ŷ���Ԫ��
    int front, rear;            // ����ָ��Ͷ�βָ��
    int tag;                    // 0 ��ʾ������ӣ�1 ��ʾ�����ӡ�
} SqQueue;

bool EnQueue(SqQueue &Q, ElementType x)
{
    if (Q.front == Q.rear && Q.tag == 1)     // ����
        return false;
    Q.data[Q.rear] = x;                      // �� x �����β
    Q.rear = (Q.rear + 1) % MaxSize;         // ��βָ��� 1 ȡģ
    Q.tag = 1;                               // �������Ϊ��ӣ��� tag Ϊ 1
    return true;
}

bool DeQueue(SqQueue &Q, ElementType &x)
{
    if (Q.front == Q.rear && Q.tag == 0)     // �ӿ�
        return false;
    x = Q.data[Q.front];                     // ����ͷԪ�ص�ֵ���� x
    Q.front = (Q.front + 1) % MaxSize;       // ��ͷָ��� 1 ȡģ
    Q.tag = 0;                               // �������Ϊ���ӣ��� tag Ϊ 0
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


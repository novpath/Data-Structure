#include <stdio.h>
#define MaxSize 100            // �洢����Ԫ�ص�������

typedef int ElementType;

typedef struct ShareStack {
    ElementType data[MaxSize]; 
    int Top0;                  // ��ջ 0 ��ջ��ָ��
    int Top1;                  // ��ջ 1 ��ջ��ָ��
} ShStack, *LinkShStack;

void InitStack(ShStack &S)  // ��ʼ��ջ��ָ��
{
    S.Top0 = -1;
    S.Top1 = MaxSize;
}

bool Push(ShStack *PtrS, ElementType x, int Tag)// Tag ��Ϊ����������ջ�ı�־��ȡֵΪ 0 �� 1
{          
    if (Tag != 0 && Tag != 1)
        return false;                             
    if (PtrS->Top1 - PtrS->Top0 == 1) {         // ����ջ��ָ�����ڣ���ջ��
        return false;
    }
    if (Tag == 0)                               // �Ե� 0 ����ջ����
        PtrS->data[++(PtrS->Top0)] = x;
    else                                        // �Ե� 1 ����ջ����
        PtrS->data[--(PtrS->Top1)] = x;
    return true;
}

bool Pop(ShStack *PtrS, ElementType &x, int Tag) // Tag ��Ϊ����������ջ�ı�־��ȡֵΪ 0 �� 1
{
    if (Tag != 0 && Tag != 1)
        return false;                         
    if (Tag == 0) {                   // �Ե� 0 ����ջ����
        if (PtrS->Top0 == -1) {       // ջ 0 ��
            return false;
        } else {
            x = PtrS->data[(PtrS->Top0)--];
            return true;
        }
    } else {                          // �Ե� 1 ����ջ����
        if (PtrS->Top1 == MaxSize) {  // ջ 1 ��
            return false;
        } else {
            x = PtrS->data[(PtrS->Top1)++];
            return true;
        }
    }
}

int main()
{
	ShStack s;
	InitStack(s);
	for (int i = 0; i < 100; i++) {
		s.data[i] = 0;
	}
	for (int i = 0; i < 100; i++) {
		printf("%3d ", s.data[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
	for (int i = 0, j = 99; i < 50; i++, j--) {
		Push(&s, i + 1, 0);
		Push(&s, j + 1, 1);
	}
	for (int i = 0; i < 100; i++) {
		printf("%3d ", s.data[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	int a, b;
	Pop(&s, a, 0);
	Pop(&s, b, 1);
	printf("a = %3d, b = %3d", a, b);

    return 0;
}


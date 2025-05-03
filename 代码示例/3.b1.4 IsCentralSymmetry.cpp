#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50           // ����ջ��Ԫ�ص�������

typedef char ElementType;

typedef struct {
    ElementType data[MaxSize];// ��̬������ջ��Ԫ��
    int top;                  // ջ��ָ��
} SqStack;

typedef struct LNode {  // ��϶��嵥����Ľ������
    ElementType data;   // ������
    struct LNode *next; // ָ����
} LNode, *LinkList; 

bool InitList(LinkList &L);
LinkList ListTailInsert(LinkList &L);
void InitStack(SqStack &S);
bool Push(SqStack &S, ElementType x);
bool Pop(SqStack &S, ElementType &x);
int Length(LinkList L);

bool IsCentralSymmetry(LinkList L)
{
	int flag = 1;
	LinkList p = L;
	SqStack s;
	
	while (p != NULL) {
		Push(s, p->data);
		p = p->next;
	}
	p = L;
	while (p != NULL) {
		ElementType x;
		Pop(s, x);
		if (p->data != x) {
			flag = 0;
			break;
		}
		p = p->next;
	}
	
	return flag;
}

bool IsCentralSymmetry2(LinkList L, int n)
{
    int i;
    char s[n / 2];
    LNode *p = L;
    for (i = 0; i < n / 2; i++) {
        s[i] = p->data;
        p = p->next;
    }
    i--;
    if (n % 2 == 1)
        p = p->next;
    while (p != NULL && s[i] == p->data) {
        i--;
        p = p->next;
    }
    if (i == -1)
        return 1;
    else
        return 0;
}

int main()
{
	LinkList L;
	InitList(L);
	ListTailInsert(L);

	printf("%d\n", IsCentralSymmetry(L));
	
	int n = Length(L);
	
	printf("%d\n", IsCentralSymmetry2(L, n));
	
    return 0;
}

/* ����ͷ���ĵ�����ĳ�ʼ�� */
bool InitList(LinkList &L)       // ����ͷ���ĵ�����ĳ�ʼ��
{
    L = NULL;                    // ͷָ��Ϊ�գ��ձ���ʱ��û���κν��
    return true;
}

/* ����ͷ����β�巨���������� */
LinkList ListTailInsert(LinkList &L)        // ˳����������
{
    int x;                                  // ���Ԫ������Ϊ����
    L = NULL;                               // ��ʼ��ͷָ��
    LNode *s, *r = NULL;                    // r Ϊ��βָ��
    while (scanf("%c", &x) && x != '\n') {  // ����һ��������ȡ��������ʾ����
        s = (LinkList)malloc(sizeof(LNode));// �����½��
        s->data = x;
        s->next = NULL;
        if (L == NULL) {                    // ����Ϊ��ʱ���½����Ϊ��һ�����
            L = s;
            r = L;
        } else {                            // ����ǿ�ʱ������β��
            r->next = s;
            r = s;
        }
    }
    return L;
}

/* ����ͷ���ĵ�������� */
int Length (LinkList L)
{ 
    int len = 0;        // ������������ʼΪ 0
    LNode *p = L;
    while (p != NULL) { 
        p = p->next;   // ����д�� p++�� p++��ָ����һ��ָ������λ�ã��� next ��ָ����һ�ṹ
        len++;         // ÿ����һ����㣬������ 1
    } 
    return len;
}

void InitStack(SqStack &S)
{
    S.top = -1;            // ��ʼ��ջ��ָ��
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

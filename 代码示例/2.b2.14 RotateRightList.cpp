#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // ��϶��嵥����Ľ������
    ElementType data;   // ������
    struct LNode *next; // ָ����
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, ElementType e);
void PrintList(LinkList &L);

LNode* RotateRightList(LinkList &L, int k)
{
    LNode *p = L, *r;
    int len = 0;
    while (p != NULL) {
        len++;
        r = p;
        p = p->next;
    }
    r->next = L;
    p = r;
    for(int i = 0; i < len - k; i++)
        p = p->next;
    L = p->next;
    p->next = NULL;

    return L;
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 4);
	ListInsert(L, 5, 5);
    RotateRightList(L, 5); 

	PrintList(L);
	
	return 0;
}

bool InitList(LinkList &L)       // ����ͷ���ĵ�����ĳ�ʼ��
{
    L = NULL;                    // ͷָ��Ϊ�գ��ձ���ʱ��û���κν��
    return true;
}

/* ����ͷ����������� */
bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                         // i ֵ�Ϸ��Լ��
        return false;
    if (i == 1) {                      // ������뵽�ײ�(i = 1)�����
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;                        // ͷָ��ָ���µĽ��
        return true;
    }
    
    LNode *p = L;                    // ָ�� p ָ��ǰɨ�赽�Ľ��
    int j = 1;                       // �������� 1 ��ʼ
    while (p != NULL && j < i - 1) { // ѭ���ҵ��� i-1 �����
        p = p->next;
        j++;
    }
    if (p == NULL)                     // i ֵ���Ϸ�
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;                 // �½���Ƚ��Ϻ�̽��
    p->next = s;                       // ǰ���������½�㣨ͬʱ�Ͽ�ԭ��̽�����ӣ�
    return true;
}

void PrintList(LinkList &L)
{
	LinkList p = L;
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

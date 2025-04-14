#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // ��϶��嵥����Ľ������
    ElementType data;   // ������
    struct LNode *next; // ָ����
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, ElementType e);
void PrintList(LinkList L);

LinkList LinkCircularList(LinkList &h1, LinkList &h2)
{
    LNode *p = h1, *q = h2;        // ����ָ�� p �� q
    while (p->next != h1)          // �ҵ� h1 ��β���
        p = p->next;
    while (q->next != h2)          // �ҵ� h2 ��β���
        q = q->next;
    p->next = h2;                  // �� h2 ���ӵ� h1 ֮��
    q->next = h1;                  // �� h2 β���ָ�� h1
    
    return h1;
}

int main()
{
	LNode *L1 = (LNode *)malloc(sizeof(LNode));
	LNode *L2 = (LNode *)malloc(sizeof(LNode));
	InitList(L1);
	InitList(L2);
	ListInsert(L1, 1, 1);
	ListInsert(L1, 2, 2);
	ListInsert(L1, 3, 3);
	ListInsert(L2, 1, 4);
	ListInsert(L2, 2, 5);
	ListInsert(L2, 3, 6);
	
	LinkCircularList(L1, L2);
	
	PrintList(L1);
	
	return 0;
}

bool InitList(LinkList &L)       // ����ͷ���ĵ�����ĳ�ʼ��
{
    L = NULL;                    // ͷָ��Ϊ�գ��ձ���ʱ��û���κν��
    return true;
}

/* ����ͷ����ѭ��������� */
bool ListInsert(LinkList &L, int i, ElementType e)
{
	if (i < 1) 	                          // i ֵ�Ϸ��Լ��
	    return false;
	if (L == NULL) {                      // ������������
	    if (i != 1) return false;         // ������ֻ�ܲ��뵽λ��1
	    
	    LNode *s = (LNode *)malloc(sizeof(LNode));
	    s->data = e;
	    s->next = s;                      // �Ի��γ�ѭ������
	    L = s;                            // ͷָ��ָ���½��
	    return true;
	}
	
	if (i == 1) {                         // ������뵽�ײ������
	    LNode *s = (LNode *)malloc(sizeof(LNode));
	    s->data = e;
	    
	    LNode *tail = L;                  // �ҵ�β���
	    while (tail->next != L)           // ѭ����ֹ����
	        tail = tail->next;
	        
	    s->next = L;                      // �½��ָ��ԭ�׽��
	    tail->next = s;                   // β���ָ�����׽��
	    L = s;                            // ����ͷָ��
	    return true;
	}
	
	LNode *p = L;                        // ָ�� p ָ��ǰɨ��Ľ��
	int j = 1;                           // ��������1��ʼ
	while (p->next != L && j < i - 1) {  // ѭ���ҵ���i-1�����
	    p = p->next;
	    j++;
	}
	
	if (j != i - 1)                      // i����������+1��ͨ��ѭ����ֹ�����жϣ�
	    return false;
	    
	LNode *s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;                   // �½���ȽӺ�̽��
	p->next = s;                         // ǰ�������½��
	return true;
}

void PrintList(LinkList L) {
    if (L == NULL) {
        return;
    }
    LinkList p = L;
    do {
        printf("%d ", p->data); // ����������Ϊint�ͣ���ʵ�����������ʽ
        p = p->next;
    } while (p != L);
}

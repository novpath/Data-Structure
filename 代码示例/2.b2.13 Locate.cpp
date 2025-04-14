#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct DNode {          // ��϶���˫����������
    ElementType data;           // ������
    int freq;
    struct DNode *prior, *next;   // ǰ���ͺ��ָ��
} DNode, *DLinkList;

bool InitDLinkList(DLinkList &L);
bool DListInsert(DLinkList &L, int i, ElementType e);
void PrintList(DLinkList L);

DLinkList Locate(DLinkList &L, ElementType x)
{
    DNode *p = L->next, *q;
    while (p != NULL && p->data != x) 
        p = p->next;
    if (p == NULL) {
        return p;
    } else {
        p->freq++;
        if (p->prior == L || p->prior->freq > p->freq) { return p; }
        if (p->next != NULL)
            p->next->prior = p->prior;
        p->prior->next = p->next;
        q = p->prior;
        while (q != L && q->freq <= p->freq) {
            q = q->prior;
        }
        p->next = q->next;
        p->prior = q;
        if (q->next != NULL)
            q->next->prior = p;
        q->next = p;
    }
    
    return p;
}

int main()
{
	DNode *L = (DNode *)malloc(sizeof(DNode));
	InitDLinkList(L);
	
	DListInsert(L, 1, 1);
	DListInsert(L, 2, 2);
	DListInsert(L, 3, 3);
	DListInsert(L, 4, 4);
	DListInsert(L, 5, 5);
	
	Locate(L, 5);
	Locate(L, 4);
	
	PrintList(L);
	
	return 0;
}

bool InitDLinkList(DLinkList &L)
{
    L = (DNode *)malloc(sizeof(DNode));  // ����һ��ͷ���
    if (L == NULL)                       // �ڴ治�㣬����ʧ��
        return false;
    L->prior = NULL;                     // ͷ���� prior ��Զָ�� NULL
    L->next = NULL;                      // ͷ���֮����ʱ��û�нڵ�
    return true;
}

/* ����ͷ����˫������� */
bool DListInsert(DLinkList &L, int i, ElementType e)
{
    if (i < 1)                        // ���λ�úϷ���
        return false;
    
    DNode *p = L;                     // pָ��ͷ���
    int j = 0;                        // ��ǰpָ����ǵ�0����㣨ͷ��㣩
    
    while (p != NULL && j < i - 1) {  // Ѱ�ҵ�i-1�����
        p = p->next;
        j++;
    }
    if (p == NULL)                    // i����������+1����Чλ��
        return false;
    
    DNode *s = (DNode *)malloc(sizeof(DNode));
    if (s == NULL)                   // �ڴ����ʧ�ܴ���
        return false;
    
    s->data = e;
    s->next = p->next;               // �½����ָ��ԭ��i�����
    s->prior = p;                    // �½��ǰ��ָ���i-1�����
    
    if (p->next != NULL) {           // ���ԭ��i��������
        p->next->prior = s;          // ԭ��i������ǰ����Ϊ�½��
    }
    
    p->next = s; // ��i-1�����ĺ�̸�Ϊ�½��
    return true;
}

void PrintList(DLinkList L)
{
	DLinkList p = L->next;
	while(p != NULL) {
		printf("[%d-%d]->", p->data, p->freq);
		p = p->next;
	}
}

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

void DeleteListSToT(LinkList &L, ElementType s, ElementType t)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *p = L->next, *pre = L;     // ��ʼ�� p �� pre
    while (p != NULL) {
        if (p->data >= s && p->data <= t) {
            pre->next = p->next;      // ��ɾ���������жϿ�
            free(p);                  // �ͷŴ�ɾ���ռ�
        } else {                      // ����pre �� p ͬ������
            pre = p;
        }
        p = pre->next;                // ������� p ָ�붼Ҫ����һ�����
    }
}

void FilterListByRange(LinkList &L, ElementType s, ElementType t)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *r = L, *p = L->next;           // r ָ��β���(ע���βָ�������)����ʼ�� r��p ָ��
    while (p != NULL) {                
        if (p->data < s || p->data > t) { // ��Ϊ s~t �Ľ��β�巨���ӵ� L β��
            r->next = p;
            r = p;
            p = p->next;                  // p ָ�����
        } else {                          // ɨ�赽�Ľ��ֵΪ x ʱ�����ͷ�
            LNode *q = p;
            p = p->next;                  // p ָ����ƣ�����һ�����˳�򲻿ɸı�
            free(q);
        }
    }
    r->next = NULL;                       // �����������β���ָ��Ϊ NULL
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	for (int i = 0; i < 10; i++) {
		ListInsert(L, i + 1, i);
	}
	DeleteListSToT(L, 2, 4);
	PrintList(L);
	printf("\n");
	FilterListByRange(L, 6, 7);
	PrintList(L);
	
	return 0;
}

bool InitList(LinkList &L)              // ��ͷ���ĵ�����ĳ�ʼ��
{
    L = (LNode *)malloc(sizeof(LNode)); // ����ͷ���
    if (L == NULL)                      // �ڴ治�㣬����ʧ��
        return false;
    L->next = NULL;                     // ͷ����ָ����Ϊ��
    return true;
}

bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                       // i ֵ�Ϸ��Լ��
        return false;
    LNode *p = L;                    // ָ�� p ָ��ǰɨ�赽�Ľ��
    int j = 0;                       // ��¼��ǰ����λ��ͷ����ǵ� 0 �����
    while (p != NULL && j < i - 1) { // ѭ���ҵ��� i-1 �����
        p = p->next;
        j++;
    }
    if (p == NULL)                   // i ֵ���Ϸ�
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;               // �½���Ƚ��Ϻ�̽��
    p->next = s;                     // ǰ���������½�㣨ͬʱ�Ͽ�ԭ��̽�����ӣ�
    return true;
}

void PrintList(LinkList &L)
{
	LinkList p = L->next;
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

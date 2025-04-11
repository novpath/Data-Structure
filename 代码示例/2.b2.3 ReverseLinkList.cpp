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

LinkList ReverseLinkList(LinkList &L)
{
    if (L == NULL || L->next == NULL)  // L �Ϸ��Լ��
        return L;
    LNode *p = L->next, *q;            // p Ϊ����ָ�룬r Ϊ p �ĺ�̣��Է�����
    L->next = NULL;                    // ͷ��� L �� next ����Ϊ NULL
    while (p != NULL) {                // ���ν�Ԫ�ؽ��ժ��
        q = p->next;                   // �ݴ� p �ĺ��
        p->next = L->next;             // �� p �����뵽ͷ���֮��
        L->next = p;
        p = q;
    }
    return L; 
}

LinkList TriPtrReverse(LinkList L)
{
    if (L == NULL)      // �ձ��ʱ��ֱ�ӷ��أ���߽�׳��
        return L;
    LNode *pre, *p = L->next, *r = p->next;
    p->next = NULL;     // �����һ�����
    while (r != NULL) { // r Ϊ�գ���˵�� p Ϊ���һ�����
        pre = p;
        p = r;
        r = r->next;
        p->next = pre;  // ָ�뷴ת
    }
    L->next = p;        // �������һ�����
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
    ReverseLinkList(L); 
	
	PrintList(L);
	printf("\n");
	ListInsert(L, 6, 6);
	ListInsert(L, 7, 7);
	ListInsert(L, 8, 8);
	ListInsert(L, 9, 9);
	ListInsert(L, 10, 10);
	TriPtrReverse(L);
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

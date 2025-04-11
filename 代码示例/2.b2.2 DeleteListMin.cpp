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

bool DeleteListMin(LinkList &L)
{
    if (L == NULL || L->next == NULL)
        return false;
    LNode *prep = L, *p = prep->next;  // p Ϊ����ָ�룬pre ָ����ǰ��
    LNode  *premin = L, *min = p;      // ������Сֵ��㼰��ǰ��
    while (p != NULL) {
        if (p->data < min->data) {
            min = p;                   // �ҵ���С�Ľ�����ǰ��ָ�뼰ָ��
            premin = prep;
        }
        prep = p;                       // ����ɨ����һ�����
        p = p->next;
    }
    premin->next = min->next;           // ɾ����Сֵ���
    free(min);
    return true;
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	ListInsert(L, 1, 2);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 1);
	ListInsert(L, 5, 5);
	DeleteListMin(L);
	
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

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

LinkList CreateListByCommonValue(LinkList LA, LinkList LB) {
    LNode *p = LA->next, *q = LB->next;
    LNode *LC = (LNode *)malloc(sizeof(LNode));         // �������� C
    LNode *r = LC;                                      // r ָ������ C ��β���
    while (p != NULL && q != NULL) {                    // ɨ�赽��һ�������
        if (p->data > q->data) {
            q = q->next;                                // ��ָ����Ԫ��С��ָ�����
        } else if (p->data < q->data) {
            p = p->next;
        } else {
            LNode * s = (LNode *)malloc(sizeof(LNode)); // �½����
            s->data = p->data;
            r->next = s;                                // *s �ӵ� LC β��
            r = s;
            p = p->next;                                // �������ɨ��
            q = q->next;
        }
    }
    r->next = NULL;                                     // ���� C ��β���ָ���ÿ�
    return LC;
}

int main()
{
	LNode *LA = (LNode *)malloc(sizeof(LNode));
	LNode *LB = (LNode *)malloc(sizeof(LNode));;
	InitList(LA);
	InitList(LB);
	
	for (int i = 0; i < 10; i++) {
		ListInsert(LA, i + 1, i);
	}
	for (int i = 0; i < 10; i++) {
		ListInsert(LB, i + 1, 2 * i);
	}
	
	LNode *LC = CreateListByCommonValue(LA, LB);
	PrintList(LC);
	
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

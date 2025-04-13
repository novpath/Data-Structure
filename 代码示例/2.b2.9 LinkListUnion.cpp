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

LinkList LinkListUnion(LinkList &LA, LinkList &LB)
{
    LNode *pa = LA->next, *pb = LB->next;    // �蹤��ָ��ֱ�Ϊ pa �� pb
    LNode *pre = LA, *t;                     // ������е�ǰ�ϲ�����ǰ��ָ�� pre����ʱָ�� t
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {          // ��������������
            pre->next = pa;                  // A �н�����ӵ������
            pre = pa;
            pa = pa->next;
            t = pb;                          // B �н���ͷ�
            pb = pb->next;
            free(t);
        } else if (pa->data < pb->data) {    // �� A �е�ǰ���ֵС�� B �е�ǰ���ֵ
            t = pa;
            pa = pa->next;                   // ����ָ��
            free(t);                         // �ͷ� A �е�ǰ���
        } else {
            t = pb;
            pb = pb->next;                   // ����ָ��
            free(t);                         // �ͷ� B �е�ǰ���
        }
    }
    while (pa) {                         // B �ѱ����꣬A δ��
        t = pa;
        pa = pa->next;
        free(t);                         // �ͷ� A ��ʣ����
    }
    while (pb) {                         // A �ѱ����꣬B δ��
        t = pb;
        pb = pb->next;
        free(t);                         // �ͷ� B ��ʣ����
    }
    pre->next = NULL;                    // �ý�������βָ��Ϊ NULL
    free(LB);                            // �ͷ� B ���ͷ���
    
    return LA;
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
	
	LinkListUnion(LA, LB);
	PrintList(LA);
	
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

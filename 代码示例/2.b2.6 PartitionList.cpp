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

LinkList PartitionList(LinkList &LA)
{
    if (LA == NULL || LA->next == NULL) return LA;
    LinkList LB = (LinkList)malloc(sizeof(LNode)); // ���� LB ��ͷ���
    LB->next = NULL;                               // ��ʼ��  LB ��
    
    LNode *p = LA->next, *q;                       // ����ָ��ָ���һ�����ݽ�㣬q ����֮���ݴ���
    LNode *ra = LA;                                // ����ָ��β����ָ�� ra
    while (p != NULL) {
        ra->next = p;                              // �� *p ���� A �ı�β
        ra = p;
        p = p->next;
        if (p != NULL) {
            q = p->next;                           // ͷ���*p ������������� q ���� *p ���
            p->next = LB->next;                    // �� *p �������� LB �ı�ͷ
            LB->next = p;
            p = q;
        }
    }
    ra->next = NULL;    // A ����β�� next ���ÿ�
    return LB;
}

int main()
{
	LNode *LA = (LNode *)malloc(sizeof(LNode));
	LNode *LB;
	InitList(LA);
	
	for (int i = 0; i < 10; i++) {
		ListInsert(LA, i + 1, i);
	}
	PrintList(LA);
	printf("\n");
	LB = PartitionList(LA);
	PrintList(LA);
	printf("\n");
	PrintList(LB);
	
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

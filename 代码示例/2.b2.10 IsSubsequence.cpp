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

bool IsSubsequence(LinkList LA, LinkList LB)
{
    LNode *pa = LA, *pb = LB;      // pa Ϊ A ����Ĺ���ָ�룬pb Ϊ B ����Ĺ���ָ�룬����ͷ���
    LNode *pre = pa;               // p ָ���¼ÿ�αȽ� A ����Ŀ�ʼ����ǰ��
    while (pa && pb) {             
        if (pa->data == pb->data) {// ���ֵ��ͬ���������Ƚ�
            pa = pa->next;
            pb = pb->next;
        } else {
            pb = LB->next;         // B ����ÿ��ƥ��ʧ�ܶ���ͷ��ʼ�Ƚ�
            pa = pre->next;        // pa ÿ�δ� p ָ����ָλ��֮��ʼ�Ƚ�
            pre = pa;              // ��¼��һ�αȽ�λ�õ�ǰ�� 
        }
    }
    if (pb == NULL)                // B ������ȫƥ��
        return true;               // B ������ A �����������
    else                           
        return false;              // B ������ A �����������
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
	for (int i = 0; i < 8; i++) {
		ListInsert(LB, i + 1, i + 2);
	}
	
	printf("%d\n", IsSubsequence(LA, LB));
	
	return 0;
}

bool InitList(LinkList &L)       // ����ͷ���ĵ�����ĳ�ʼ��
{
    L = NULL;                    // ͷָ��Ϊ�գ��ձ���ʱ��û���κν��
    return true;
}

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

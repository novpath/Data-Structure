#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // ��϶��嵥����Ľ������
    ElementType data;   // ������
    struct LNode *next; // ָ����
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool IsEmpty(LinkList L);
int Length (LinkList L);
LNode *GetElem(LinkList L, int i);
LNode *LocateElem(LinkList L, ElementType e);
bool ListInsert(LinkList &L, int i, ElementType e);
bool ListDelete(LinkList &L, int i, ElementType &e);
void PrintList(LinkList &L);

void DeleteListX(LinkList &L, ElementType x)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *p = L->next, *pre = L;     // ��ʼ�� p �� pre
    while (p != NULL) {
        if (p->data == x) {
            pre->next = p->next;      // ��ɾ���������жϿ�
            free(p);                  // �ͷŴ�ɾ���ռ�
        } else {                      // ����pre �� p ͬ������
            pre = p;
        }
        p = pre->next;                // ������� p ָ�붼Ҫ����һ�����
    }
}

void CreateListLackingX(LinkList &L, ElementType x)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *r = L, *p = L->next;    // r ָ��β���(ע���βָ�������)����ʼ�� r��p ָ��
    while (p != NULL) {                
        if (p->data != x) {        // ��Ϊ x �Ľ��β�巨���ӵ� L β��
            r->next = p;
            r = p;
        } else {                   // ɨ�赽�Ľ��ֵΪ x ʱ�����ͷ�
            LNode *q = p;
            free(q);
        }
        p = p->next;               // �������������p ��Ҫ����һ�����
    }
    r->next = NULL;                // �����������β���ָ��Ϊ NULL
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 1);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 1);
	ListInsert(L, 5, 5);
	DeleteListX(L, 1); 
	PrintList(L);
	
	printf("\n");
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 5);
	ListInsert(L, 5, 5);
	DeleteListX(L, 3); 
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

bool IsEmpty(LinkList L)
{
    if (L->next == NULL)
        return true;
    else
        return false;
}

int Length (LinkList L)
{ 
    int len = 0;        // ������������ʼΪ 0
    LNode *p = L;
    while (p->next != NULL) { 
        p = p->next;   // ����д�� p++�� p++��ָ����һ��ָ������λ�ã��� next ��ָ����һ�ṹ
        len++;         // ÿ����һ����㣬������ 1
    } 
    return len;
}

LNode *GetElem(LinkList L, int i)
{
    if (i < 1)
        return NULL;              // �Ƿ�λ�÷��� NULL, i = 0 ��Ϊͷ���Ҳ����
    LNode *p = L;                 // ָ�� p ָ��ǰɨ�赽�Ľ��
    int j = 0;                    // ��¼��ǰ����λ��ͷ����ǵ� 0 �����
    while (p != NULL && j < i) {  // ѭ���ҵ��� i �����
        p = p->next;
        j++; 
    }
    return p;                     // �ҵ��� i ��������ָ�룬Խ���򷵻� NULL
}

LNode *LocateElem(LinkList L, ElementType e)
{
    LNode *p = L->next;                // ����ͷ��㣬�ӵ�һ�����ݽ�㿪ʼ
    while (p != NULL && p->data != e)  // �ӵ�һ����㿪ʼ����������Ϊ e �Ľ��
        p = p->next; 
    return p;                          // ���ҳɹ����ظý���ָ�룬���򷵻� NULL
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

bool ListDelete(LinkList &L, int i, ElementType &e)
{
    if (i < 1)                        // ��� i �ĺϷ���
        return false;
    LNode *p = L;                     // ָ�� p ָ��ǰɨ�赽�Ľ��
    int j = 0;                        // ��¼��ǰ����λ��ͷ����ǵ� 0 �����
    while (p != NULL && j < i - 1) {  // ѭ���ҵ��� i-1 ����㣨��ɾ���ǰ����
        p = p->next;
        j++;
    }
    if (p == NULL || p->next == NULL)  // ǰ�����ߴ�ɾ��㲻���ڣ���ɾ��ʧ��
        return false;
    LNode *q = p->next;                // �� q ָ���ɾ����㣨�� i ����㣩
    e = q->data;                       // �����ͱ��� e ����Ԫ�ص�ֵ
    p->next = q->next;                 // �޸�����ָ�룬���� *q ���
    free(q);                           // �ͷŽ�� malloc() �Ĵ洢�ռ�
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

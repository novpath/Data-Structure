#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // 混合定义单链表的结点类型
    ElementType data;   // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, ElementType e);
void PrintList(LinkList &L);

LNode* RotateRightList(LinkList &L, int k)
{
    LNode *p = L, *r;
    int len = 0;
    while (p != NULL) {
        len++;
        r = p;
        p = p->next;
    }
    r->next = L;
    p = r;
    for(int i = 0; i < len - k; i++)
        p = p->next;
    L = p->next;
    p->next = NULL;

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
    RotateRightList(L, 5); 

	PrintList(L);
	
	return 0;
}

bool InitList(LinkList &L)       // 不带头结点的单链表的初始化
{
    L = NULL;                    // 头指针为空，空表，暂时还没有任何结点
    return true;
}

/* 不带头结点的链表插入 */
bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                         // i 值合法性检查
        return false;
    if (i == 1) {                      // 处理插入到首部(i = 1)的情况
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;                        // 头指针指向新的结点
        return true;
    }
    
    LNode *p = L;                    // 指针 p 指向当前扫描到的结点
    int j = 1;                       // 计数器从 1 开始
    while (p != NULL && j < i - 1) { // 循环找到第 i-1 个结点
        p = p->next;
        j++;
    }
    if (p == NULL)                     // i 值不合法
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;                 // 新结点先接上后继结点
    p->next = s;                       // 前驱结点接上新结点（同时断开原后继结点连接）
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

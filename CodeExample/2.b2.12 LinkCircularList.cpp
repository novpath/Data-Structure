#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // 混合定义单链表的结点类型
    ElementType data;   // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, ElementType e);
void PrintList(LinkList L);

LinkList LinkCircularList(LinkList &h1, LinkList &h2)
{
    LNode *p = h1, *q = h2;        // 工作指针 p 和 q
    while (p->next != h1)          // 找到 h1 的尾结点
        p = p->next;
    while (q->next != h2)          // 找到 h2 的尾结点
        q = q->next;
    p->next = h2;                  // 将 h2 链接到 h1 之后
    q->next = h1;                  // 将 h2 尾结点指向 h1
    
    return h1;
}

int main()
{
	LNode *L1 = (LNode *)malloc(sizeof(LNode));
	LNode *L2 = (LNode *)malloc(sizeof(LNode));
	InitList(L1);
	InitList(L2);
	ListInsert(L1, 1, 1);
	ListInsert(L1, 2, 2);
	ListInsert(L1, 3, 3);
	ListInsert(L2, 1, 4);
	ListInsert(L2, 2, 5);
	ListInsert(L2, 3, 6);
	
	LinkCircularList(L1, L2);
	
	PrintList(L1);
	
	return 0;
}

bool InitList(LinkList &L)       // 不带头结点的单链表的初始化
{
    L = NULL;                    // 头指针为空，空表，暂时还没有任何结点
    return true;
}

/* 不带头结点的循环链表插入 */
bool ListInsert(LinkList &L, int i, ElementType e)
{
	if (i < 1) 	                          // i 值合法性检查
	    return false;
	if (L == NULL) {                      // 处理空链表插入
	    if (i != 1) return false;         // 空链表只能插入到位置1
	    
	    LNode *s = (LNode *)malloc(sizeof(LNode));
	    s->data = e;
	    s->next = s;                      // 自环形成循环链表
	    L = s;                            // 头指针指向新结点
	    return true;
	}
	
	if (i == 1) {                         // 处理插入到首部的情况
	    LNode *s = (LNode *)malloc(sizeof(LNode));
	    s->data = e;
	    
	    LNode *tail = L;                  // 找到尾结点
	    while (tail->next != L)           // 循环终止条件
	        tail = tail->next;
	        
	    s->next = L;                      // 新结点指向原首结点
	    tail->next = s;                   // 尾结点指向新首结点
	    L = s;                            // 更新头指针
	    return true;
	}
	
	LNode *p = L;                        // 指针 p 指向当前扫描的结点
	int j = 1;                           // 计数器从1开始
	while (p->next != L && j < i - 1) {  // 循环找到第i-1个结点
	    p = p->next;
	    j++;
	}
	
	if (j != i - 1)                      // i超过链表长度+1（通过循环终止条件判断）
	    return false;
	    
	LNode *s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;                   // 新结点先接后继结点
	p->next = s;                         // 前驱结点接新结点
	return true;
}

void PrintList(LinkList L) {
    if (L == NULL) {
        return;
    }
    LinkList p = L;
    do {
        printf("%d ", p->data); // 假设数据域为int型，按实际情况调整格式
        p = p->next;
    } while (p != L);
}

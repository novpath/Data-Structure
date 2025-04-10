#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // 混合定义单链表的结点类型
    ElementType data;   // 数据域
    struct LNode *next; // 指针域
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
    LNode *p = L->next, *pre = L;     // 初始化 p 和 pre
    while (p != NULL) {
        if (p->data == x) {
            pre->next = p->next;      // 待删结点从链表中断开
            free(p);                  // 释放待删结点空间
        } else {                      // 否则，pre 和 p 同步后移
            pre = p;
        }
        p = pre->next;                // 两种情况 p 指针都要后移一个结点
    }
}

void CreateListLackingX(LinkList &L, ElementType x)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *r = L, *p = L->next;    // r 指向尾结点(注意和尾指针的区别)，初始化 r、p 指针
    while (p != NULL) {                
        if (p->data != x) {        // 不为 x 的结点尾插法连接到 L 尾部
            r->next = p;
            r = p;
        } else {                   // 扫描到的结点值为 x 时将其释放
            LNode *q = p;
            free(q);
        }
        p = p->next;               // 无论哪种情况，p 都要后移一个结点
    }
    r->next = NULL;                // 插入结束后置尾结点指针为 NULL
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

bool InitList(LinkList &L)              // 带头结点的单链表的初始化
{
    L = (LNode *)malloc(sizeof(LNode)); // 创建头结点
    if (L == NULL)                      // 内存不足，分配失败
        return false;
    L->next = NULL;                     // 头结点的指针域为空
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
    int len = 0;        // 计数变量，初始为 0
    LNode *p = L;
    while (p->next != NULL) { 
        p = p->next;   // 不能写成 p++， p++是指向下一个指针类型位置，而 next 是指向下一结构
        len++;         // 每访问一个结点，计数加 1
    } 
    return len;
}

LNode *GetElem(LinkList L, int i)
{
    if (i < 1)
        return NULL;              // 非法位置返回 NULL, i = 0 作为头结点也可以
    LNode *p = L;                 // 指针 p 指向当前扫描到的结点
    int j = 0;                    // 记录当前结点的位序，头结点是第 0 个结点
    while (p != NULL && j < i) {  // 循环找到第 i 个结点
        p = p->next;
        j++; 
    }
    return p;                     // 找到第 i 个，返回指针，越界则返回 NULL
}

LNode *LocateElem(LinkList L, ElementType e)
{
    LNode *p = L->next;                // 跳过头结点，从第一个数据结点开始
    while (p != NULL && p->data != e)  // 从第一个结点开始查找数据域为 e 的结点
        p = p->next; 
    return p;                          // 查找成功返回该结点的指针，否则返回 NULL
}

bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                       // i 值合法性检查
        return false;
    LNode *p = L;                    // 指针 p 指向当前扫描到的结点
    int j = 0;                       // 记录当前结点的位序，头结点是第 0 个结点
    while (p != NULL && j < i - 1) { // 循环找到第 i-1 个结点
        p = p->next;
        j++;
    }
    if (p == NULL)                   // i 值不合法
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;               // 新结点先接上后继结点
    p->next = s;                     // 前驱结点接上新结点（同时断开原后继结点连接）
    return true;
}

bool ListDelete(LinkList &L, int i, ElementType &e)
{
    if (i < 1)                        // 检查 i 的合法性
        return false;
    LNode *p = L;                     // 指针 p 指向当前扫描到的结点
    int j = 0;                        // 记录当前结点的位序，头结点是第 0 个结点
    while (p != NULL && j < i - 1) {  // 循环找到第 i-1 个结点（待删结点前驱）
        p = p->next;
        j++;
    }
    if (p == NULL || p->next == NULL)  // 前驱或者待删结点不存在，则删除失败
        return false;
    LNode *q = p->next;                // 令 q 指向待删除结点（第 i 个结点）
    e = q->data;                       // 引用型变量 e 返回元素的值
    p->next = q->next;                 // 修改链表指针，跳过 *q 结点
    free(q);                           // 释放结点 malloc() 的存储空间
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

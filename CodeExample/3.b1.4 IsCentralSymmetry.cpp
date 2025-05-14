#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50           // 定义栈中元素的最大个数

typedef char ElementType;

typedef struct {
    ElementType data[MaxSize];// 静态数组存放栈中元素
    int top;                  // 栈顶指针
} SqStack;

typedef struct LNode {  // 混合定义单链表的结点类型
    ElementType data;   // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList; 

bool InitList(LinkList &L);
LinkList ListTailInsert(LinkList &L);
void InitStack(SqStack &S);
bool Push(SqStack &S, ElementType x);
bool Pop(SqStack &S, ElementType &x);
int Length(LinkList L);

bool IsCentralSymmetry(LinkList L)
{
	int flag = 1;
	LinkList p = L;
	SqStack s;
	
	while (p != NULL) {
		Push(s, p->data);
		p = p->next;
	}
	p = L;
	while (p != NULL) {
		ElementType x;
		Pop(s, x);
		if (p->data != x) {
			flag = 0;
			break;
		}
		p = p->next;
	}
	
	return flag;
}

bool IsCentralSymmetry2(LinkList L, int n)
{
    int i;
    char s[n / 2];
    LNode *p = L;
    for (i = 0; i < n / 2; i++) {
        s[i] = p->data;
        p = p->next;
    }
    i--;
    if (n % 2 == 1)
        p = p->next;
    while (p != NULL && s[i] == p->data) {
        i--;
        p = p->next;
    }
    if (i == -1)
        return 1;
    else
        return 0;
}

int main()
{
	LinkList L;
	InitList(L);
	ListTailInsert(L);

	printf("%d\n", IsCentralSymmetry(L));
	
	int n = Length(L);
	
	printf("%d\n", IsCentralSymmetry2(L, n));
	
    return 0;
}

/* 不带头结点的单链表的初始化 */
bool InitList(LinkList &L)       // 不带头结点的单链表的初始化
{
    L = NULL;                    // 头指针为空，空表，暂时还没有任何结点
    return true;
}

/* 不带头结点的尾插法建立单链表 */
LinkList ListTailInsert(LinkList &L)        // 顺序建立单链表
{
    int x;                                  // 结点元素类型为整形
    L = NULL;                               // 初始化头指针
    LNode *s, *r = NULL;                    // r 为表尾指针
    while (scanf("%c", &x) && x != '\n') {  // 输入一个不可能取到的数表示结束
        s = (LinkList)malloc(sizeof(LNode));// 创建新结点
        s->data = x;
        s->next = NULL;
        if (L == NULL) {                    // 链表为空时，新结点作为第一个结点
            L = s;
            r = L;
        } else {                            // 链表非空时，插入尾部
            r->next = s;
            r = s;
        }
    }
    return L;
}

/* 不带头结点的单链表求表长 */
int Length (LinkList L)
{ 
    int len = 0;        // 计数变量，初始为 0
    LNode *p = L;
    while (p != NULL) { 
        p = p->next;   // 不能写成 p++， p++是指向下一个指针类型位置，而 next 是指向下一结构
        len++;         // 每访问一个结点，计数加 1
    } 
    return len;
}

void InitStack(SqStack &S)
{
    S.top = -1;            // 初始化栈顶指针
}

bool Push(SqStack &S, ElementType x)
{
    if (S.top == MaxSize - 1)     // 栈满，报错
        return false;
    S.data[++S.top] = x;          // 指针先加 1，再入栈
    return true;
}

bool Pop(SqStack &S, ElementType &x)
{
    if (S.top == -1)        // 栈空，报错
        return false;
    x = S.data[S.top--];    // 先出栈，指针再减 1
    return true;
}

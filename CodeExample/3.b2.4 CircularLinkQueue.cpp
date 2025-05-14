#include <stdio.h>
#include <stdlib.h>

typedef int ElementType; 

typedef struct LinkNode {
    ElementType data;
    struct LinkNode *next;
} LNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

bool Enqueue(LinkQueue &Q, ElementType x)
{
    if (Q.front == Q.rear->next) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        if (s == NULL)
            return false;
        s->data = x;
        s->next = Q.rear->next;
        Q.rear->next = s;
        Q.rear = s;
    } else {
        Q.rear->data = x;
        Q.rear = Q.rear->next;
    }
    return true;
}

bool Dequeue(LinkQueue &Q, ElementType &x)
{
    if (Q.front == Q.rear)
        return false;
    Q.front = Q.front->next;    // front 移动到队头
    x = Q.front->data;        // 取队头元素
    return true;
}

void PrintQueue(LinkQueue Q)
{
	LNode *p = Q.front;
	while (p != Q.rear) {
		printf("%d", p->next->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	LinkQueue Q;
	ElementType x;
	LNode *Head = (LNode *)malloc(sizeof(LNode));
	Head->next = Head;
	Q.front = Q.rear = Head;
	Enqueue(Q, 1);
	Enqueue(Q, 2);
	Enqueue(Q, 3);
	PrintQueue(Q);
	Dequeue(Q, x);
	PrintQueue(Q);
	printf("x = %d", x);

    return 0;
}


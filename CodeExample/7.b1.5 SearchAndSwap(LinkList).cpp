#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define MaxLength 100

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;

int SearchAndSwap(LinkList L, int x)
{
    int i = 0;
    LinkList p = L->next, pre = L;
    while (p != NULL && p->data != x) {
        i++;
        pre = p;
        p = p->next;
    }
    if (p != NULL && i >= 1) {
        int temp = p->data;
        p->data = pre->data;
        pre->data = temp;
        i--;
    }

    return p == NULL ? -1 : i;
}

void Insert(LinkList &r, int x)
{
    LinkList s = (LinkList) malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    r->next = s;
    r = s;
}

int main()
{
    LinkList L = (LinkList) malloc(sizeof(LinkNode));
    L->next = NULL;
    LinkList r = L;
    Insert(r, 3);
    Insert(r, 7);
    Insert(r, 11);
    Insert(r, 18);

    printf("%d", SearchAndSwap(L, 18));

    free(L);
    return 0;
}

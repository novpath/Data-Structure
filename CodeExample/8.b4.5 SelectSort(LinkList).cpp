#include <cstdio>
#include <cstdlib>
#define NULL nullptr

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SelectSort(LinkList L)
{
    LinkList p = L->next;
    while (p != NULL) {
        LinkList min = p;
        for (LinkList q = p->next; q != NULL; q = q->next)
            if (q->data < min->data) min = q;
        if (min != p) Swap(p->data, min->data);
        p = p->next;
    }
}

void Insert(LinkList L, int data, LinkList &r)
{
    LinkList s = (LNode *) malloc(sizeof(LNode));
    s->data = data;
    s->next = NULL;
    r->next = s;
    r = s;
}

void PrintList(LinkList L)
{
    LinkList p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main()
{
    LinkList L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    if (L == NULL)
        return -1;
    LinkList r = L;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        Insert(L, data, r);
    }
    SelectSort(L);
    PrintList(L);
    free(L);
    return 0;
}

#include <cstdio>
#include <cstdlib>
#define NULL nullptr

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void SelectSort(LinkList L)
{
    LinkList p = L->next;
    L->next = NULL;
    while (p != NULL) {
        LinkList max = p, maxPre = NULL, pre = NULL;
        for (LinkList q = p; q != NULL; pre = q, q = q->next)
            if (q->data > max->data) {
                max = q;
                maxPre = pre;
            }
        if (maxPre == NULL)
            p = p->next;
        else
            maxPre->next = max->next;
        max->next = L->next;
        L->next = max;
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

void FreeLinkList(LinkList L)
{
    LinkList p = L;
    while (p) {
        LinkList t = p;
        p = p->next;
        free(t);
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
    FreeLinkList(L);
    return 0;
}

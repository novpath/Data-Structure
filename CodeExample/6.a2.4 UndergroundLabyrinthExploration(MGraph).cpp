#include <cstdio>
#include <cstdlib>

#define NULL nullptr
/* -------- 图的邻接表表示法 ---------- */
#define MaxVertexNum 1000

typedef int VertexType;

typedef struct MGNode {
    int vexnum, arcnum;
    int edge[MaxVertexNum][MaxVertexNum];
    VertexType s;           /* 探索起点 */
} MGNode, *MGraph;

bool Visited[MaxVertexNum];

MGraph CreateGraph();
MGraph BuildGraph();
/* -------- 图的定义结束 ---------- */

/* -------- 堆栈的定义 ---------- */
typedef VertexType ElementType;

typedef struct SNode {
    ElementType data;
    struct SNode *next;
} SNode, *Stack;

Stack InitStack();
bool Push(Stack S, ElementType e);
ElementType Pop(Stack S);
ElementType GetTop(Stack S);
/* -------- 堆栈的定义结束 ---------- */

void NonRec_DFS(MGraph G, VertexType v);

int main()
{
    MGraph G = BuildGraph();

    NonRec_DFS(G, G->s);
    VertexType v;
    for (v = 0; v < G->vexnum; v++)
        if (!Visited[v]) break;
    if (v < G->vexnum)
        printf(" 0\n");
    else
        printf("\n");

    free(G);
    return 0;
}

MGraph CreateGraph()
{
    MGraph G = (MGraph) malloc(sizeof(struct MGNode));
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &G->s);
    for (VertexType v = 0; v < G->vexnum; v++) {
        Visited[v] = false;
        for (VertexType w = 0; w < G->vexnum; w++) {
            G->edge[v][w] = 0;
        }
    }
    return G;
}

MGraph BuildGraph()
{
    MGraph G = CreateGraph();
    G->s--;
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        v--;
        w--;
        G->edge[v][w] = 1;
        G->edge[w][v] = 1;
    }
    return G;
}

Stack InitStack()
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    if (!S) return NULL;
    S->next = NULL;
    return S;
}

bool IsStackEmpty(Stack S)
{
    if (S == NULL)
        return false;
    return (S->next == NULL);
}

bool Push(Stack S, ElementType e)
{
    if (S == NULL)
        return false;
    Stack tmp = (Stack) malloc(sizeof(struct SNode));
    tmp->data = e;
    tmp->next = S->next;
    S->next = tmp;
    return true;
}

ElementType Pop(Stack S)
{
    if (S == NULL || IsStackEmpty(S))
        return -1;
    Stack top = S->next;
    ElementType TopTlem = top->data;
    S->next = top->next;
    free(top);
    return TopTlem;
}

ElementType GetTop(Stack S)
{
    if (S == NULL || IsStackEmpty(S))
        return -1;
    return S->next->data;
}

void NonRec_DFS(MGraph G, VertexType v)
{
    Stack S = InitStack();          // 记录访问足迹，相当于放绳路径

    Visited[v] = true;              // 标记访问到的结点，相当于点灯
    printf("%d", v + 1);      // 点灯序号
    Push(S, v);                     // 记录访问路线，相当于放绳操作
    while (!IsStackEmpty(S)) {
        v = GetTop(S);
        VertexType w;
        for (w = 0; w < G->vexnum; w++) {
            if (!Visited[w] && G->edge[v][w]) {
                Visited[w] = true;
                printf(" %d", w + 1); // 点灯
                Push(S, w);                 // 放绳
                break;
            }
        }
        if (w == G->vexnum) {               // 邻接点都已经点亮了
            Pop(S);
            if (!IsStackEmpty(S))
                printf(" %d", GetTop(S) + 1);
        }
    }
}

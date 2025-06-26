#include <cstdio>
#include <cstdlib>

#define NULL nullptr
/* -------- 图的邻接表表示法 ---------- */
#define MaxVertexNum 1000

typedef int VertexType;

typedef struct ArcNode {
    VertexType adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct ALGNode {
    int vexnum, arcnum;
    AdjList vertices;
    VertexType s;           /* 探索起点 */
} ALGNode, *ALGraph;

bool Visited[MaxVertexNum];

ALGraph CreateGraph();
void AddEdge(ALGraph G);
ALGraph BuildGraph();
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

void NonRec_DFS(ALGraph G, VertexType v);

int main()
{
    ALGraph G = BuildGraph();

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

ALGraph CreateGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(struct ALGNode));
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &G->s);
    for (VertexType v = 0; v < G->vexnum; v++) {
        Visited[v] = false;
        G->vertices[v].firstarc = (ArcNode *) malloc(sizeof(ArcNode));
        G->vertices[v].firstarc->nextarc = NULL;    /* 建链表空头结点 */
    }
    return G;
}

void AddEdge(ALGraph G, int v, int w)
{
    /* 建立弧 <v,w>*/
    ArcNode *arc_vw = (ArcNode *) malloc(sizeof(ArcNode));
    arc_vw->adjvex = w;
    arc_vw->nextarc = NULL;
    ArcNode *p = G->vertices[v].firstarc;
    while (p->nextarc != NULL && (p->nextarc->adjvex < arc_vw->adjvex))
        p = p->nextarc;
    arc_vw->nextarc = p->nextarc;
    p->nextarc = arc_vw;
    /* 建立弧 <w,v>*/
    ArcNode *arc_wv = (ArcNode *) malloc(sizeof(ArcNode));
    arc_wv->adjvex = v;
    arc_wv->nextarc = NULL;
    p = G->vertices[w].firstarc;
    while (p->nextarc != NULL && (p->nextarc->adjvex < arc_wv->adjvex))
        p = p->nextarc;
    arc_wv->nextarc = p->nextarc;
    p->nextarc = arc_wv;
}

ALGraph BuildGraph()
{
    ALGraph G = CreateGraph();
    G->s--;
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        AddEdge(G, v - 1, w - 1);
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

void NonRec_DFS(ALGraph G, VertexType v)
{
    Stack S = InitStack();          // 记录访问足迹，相当于放绳路径

    Visited[v] = true;              // 标记访问到的结点，相当于点灯
    printf("%d", v + 1);      // 点灯序号
    Push(S, v);                     // 记录访问路线，相当于放绳操作
    ArcNode *p;
    while (!IsStackEmpty(S)) {
        v = GetTop(S);
        for (p = G->vertices[v].firstarc->nextarc; p != NULL; p = p->nextarc) {
            if (!Visited[p->adjvex]) {
                Visited[p->adjvex] = true;
                printf(" %d", p->adjvex + 1); // 点灯
                Push(S, p->adjvex);                 // 放绳
                break;
            }
        }
        if (p == NULL) {         // 邻接点都已经点亮了
            Pop(S);
            if (!IsStackEmpty(S))
                printf(" %d", GetTop(S) + 1);
        }
    }
}

#include <cstdio>

#define NULL nullptr
#define MaxSize 100

typedef int VertexType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxSize];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void InitGraph(ALGraph &G, int vexnum, int arcnum);
void AddEdge(ALGraph &G, int v, int w);
ALGraph CreateGraph(int vexnum, int arcnum);
void DestroyGraph(ALGraph &G);

int visited[MaxSize], path[MaxSize];

void PrintSimplePath(const ALGraph &G, int u, int v, int scanLen)
{
    path[scanLen] = u;
    visited[u] = true;
    if (u == v) {
        for (int i = 0; i <= scanLen; i++)
            printf(" %d", path[i]);
        printf("\n");
    }

    for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
        int neighbor = p->adjvex;
        if (visited[neighbor] == false)
            PrintSimplePath(G, neighbor, v, scanLen + 1);
    }
    visited[u] = false;
}

int main()
{
    int vexnum, arcnum;
    printf("Input Vex Number and Arc Number:");
    scanf("%d %d", &vexnum, &arcnum);
    ALGraph G = CreateGraph(vexnum, arcnum);

    int vi, vj;
    printf("Input Vi Node and Vj Node:");
    scanf("%d %d", &vi, &vj);
    printf("The Path Vi to Vj:\n");

    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;

    PrintSimplePath(G, vi, vj, 0);
    DestroyGraph(G);
    return 0;
}

void InitGraph(ALGraph &G, int vexnum, int arcnum)
{
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 0; i < vexnum; i++) {
        G.vertices[i].data = i;
        G.vertices[i].firstarc = NULL;
    }
}

void AddEdge(ALGraph &G, int v, int w)
{
    // 添加 v->w 的边
    ArcNode *arc_vw = new ArcNode;
    arc_vw->adjvex = w;
    arc_vw->nextarc = G.vertices[v].firstarc;
    G.vertices[v].firstarc = arc_vw;
}

ALGraph CreateGraph(int vexnum, int arcnum)
{
    ALGraph G;
    InitGraph(G, vexnum, arcnum);

    for (int i = 0; i < arcnum; i++) {
        int x, y;
        printf("Add edge x to y:");
        scanf("%d %d", &x, &y);
        AddEdge(G, x, y);
    }

    return G;
}

void DestroyGraph(ALGraph &G)
{
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            delete temp;
        }
        G.vertices[i].firstarc = NULL;
    }
}

/* 输入样例：
4 5
0 1
0 2
1 2
1 3
2 3
0 3

 */

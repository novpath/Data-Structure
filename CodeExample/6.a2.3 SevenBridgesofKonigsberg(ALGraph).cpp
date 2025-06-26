#include <cstdio>
#include <cstdlib>

#define MaxVertexNum 1000
typedef int VertexType;
typedef int EdgeType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    struct ArcNode *firstarc;
    int degree;
} VNode, AdjList[MaxVertexNum];

typedef struct ALGNode {
    int vexnum, arcnum;
    AdjList vertices;
} ALGNode, *ALGraph;

bool visited[MaxVertexNum];

ALGraph CreateGraph();
ALGraph BuildGraph();
void DFS(ALGraph G, int v);
bool CheckG(ALGraph G);
void AddEdge(ALGraph G, int v, int w);

int main()
{
    ALGraph G = BuildGraph();
    DFS(G, 0);
    int v;
    for (v = 0; v < G->vexnum; v++)
        if (!visited[v]) break;
    if (v < G->vexnum)
        printf("0\n");
    else
        printf("%d\n", CheckG(G));

    return 0;
}

ALGraph CreateGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(struct ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        G->vertices[v].degree = 0;
        visited[v] = false;
        G->vertices[v].firstarc = NULL;
    }

    return G;
}

void AddEdge(ALGraph G, int v, int w)
{
    // 添加 v->w 的边
    ArcNode *arc_vw = (ArcNode *) malloc(sizeof(ArcNode));
    arc_vw->adjvex = w;
    arc_vw->nextarc = G->vertices[v].firstarc;
    G->vertices[v].firstarc = arc_vw;
    // 添加 w->v 的边
    ArcNode *arc_wv = (ArcNode *) malloc(sizeof(ArcNode));
    arc_wv->adjvex = v;
    arc_wv->nextarc = G->vertices[w].firstarc;
    G->vertices[w].firstarc = arc_wv;
}

ALGraph BuildGraph()
{
    ALGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        AddEdge(G, v - 1, w - 1);
        G->vertices[v - 1].degree++;
        G->vertices[w - 1].degree++;
    }
    return G;
}

void DFS(ALGraph G, int v)
{
    visited[v] = true;
    for (ArcNode *p = G->vertices[v].firstarc; p != NULL; p = p->nextarc) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}

bool CheckG(ALGraph G)
{
    for (int v = 0; v < G->vexnum; v++)
        if (G->vertices[v].degree % 2 == 1)
            return false;
    return true;
}

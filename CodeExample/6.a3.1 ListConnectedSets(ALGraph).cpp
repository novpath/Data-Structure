#include <cstdio>
#include <stdlib.h>

#define NULL nullptr
#define MaxVertexNum 100

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
} ALGNode, *ALGraph;

void AddEdge(ALGraph G, int v, int w)
{
    ArcNode *arc_vw = (ArcNode *) malloc(sizeof(ArcNode));
    arc_vw->adjvex = w;
    ArcNode *p = G->vertices[v].firstarc;
    while (p->nextarc != NULL && p->nextarc->adjvex < w)
        p = p->nextarc;
    arc_vw->nextarc = p->nextarc;
    p->nextarc = arc_vw;

    ArcNode *arc_wv = (ArcNode *) malloc(sizeof(ArcNode));
    arc_wv->adjvex = v;
    p = G->vertices[w].firstarc;
    while (p->nextarc != NULL && p->nextarc->adjvex < v)
        p = p->nextarc;
    arc_wv->nextarc = p->nextarc;
    p->nextarc = arc_wv;
}

ALGraph BuildGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        ArcNode *head = (ArcNode *) malloc(sizeof(ArcNode));
        G->vertices[v].firstarc = head;
        head->nextarc = NULL;
    }
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        AddEdge(G, v, w);
    }
    return G;
}

bool Visited[MaxVertexNum];

void DFS(ALGraph G, int v)
{
    printf("%d ", v);
    Visited[v] = true;
    for (ArcNode *p = G->vertices[v].firstarc; p; p = p->nextarc) {
        int w = p->adjvex;
        if (!Visited[w]) {
            DFS(G, w);
        }
    }
}

void DFSTraverse(ALGraph G)
{
    for (int i = 0; i < G->vexnum; i++)
        Visited[i] = false;
    for (int v = 0; v < G->vexnum; v++) {
        if (!Visited[v]) {
            printf("{ ");
            DFS(G, v);
            printf("}\n");
        }
    }
}

typedef int Queue[MaxVertexNum];

void BFS(ALGraph G, int v)
{
    Queue Q;
    int front = 0, rear = 0;
    Q[rear++] = v;
    printf("%d ", v);
    Visited[v] = true;
    while (front != rear) {
        v = Q[front++];
        for (ArcNode *p = G->vertices[v].firstarc->nextarc; p; p = p->nextarc) {
            int w = p->adjvex;
            if (!Visited[w]) {
                printf("%d ", w);
                Visited[w] = true;
                Q[rear++] = w;
            }
        }
    }
}

void BFSTraverse(ALGraph G)
{
    for (int i = 0; i < G->vexnum; i++)
        Visited[i] = false;
    for (int v = 0; v < G->vexnum; v++) {
        if (!Visited[v]) {
            printf("{ ");
            BFS(G, v);
            printf("}\n");
        }
    }
}

int main()
{
    ALGraph G = BuildGraph();
    DFSTraverse(G);
    BFSTraverse(G);

    free(G);
    return 0;
}

#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxVertexNum 100

typedef int VertexType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

void InitGraph(ALGraph &G, int vexnum, int arcnum);
void AddEdge(ALGraph &G, int v, int w);
ALGraph CreateGraph(int vexnum, int arcnum);
void DestroyGraph(ALGraph &G);

bool DFS(const ALGraph &G, int v, int w, int visited[])
{
    if (w == v)
        return true;
    visited[v] = true;
    for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
        int neighbor = p->adjvex;
        if (!visited[neighbor] && DFS(G, neighbor, w, visited)) {
            return true;
        }
    }
    return false;
}

bool PathExist(const ALGraph &G, int v, int w)
{
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) {
        return false;
    }
    int *visited = (int *) malloc(sizeof(int) * G.vexnum);
    if (visited == NULL)
        return false;
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;

    int *q = (int *) malloc(sizeof(int) * G.vexnum);
    int front = 0, rear = 0;
    q[rear++] = v;
    visited[v] = true;
    while (front != rear) {
        int j = q[front++];
        for (ArcNode *p = G.vertices[j].firstarc; p; p = p->nextarc) {
            int neighbor = p->adjvex;
            if (neighbor == w) {
                free(visited);
                free(q);
                return true;
            }
            if (visited[neighbor] == false) {
                visited[neighbor] = true;
                q[rear++] = neighbor;
            }
        }
    }

    free(visited);
    free(q);
    return false;
}

int main()
{
    int vexnum, arcnum;
    printf("Input Vex Number and Arc Number:");
    scanf("%d %d", &vexnum, &arcnum);
    ALGraph G = CreateGraph(vexnum, arcnum);

    int i, j;
    printf("Input i Node and j Node:");
    scanf("%d %d", &i, &j);
    printf("The Path between i and j %s existed!\n",
           PathExist(G, i, j) ? "is" : "is no");
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

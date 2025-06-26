#include <cstdio>
#include <cstdlib>

#define MaxVertexNum 1000
typedef int VertexType;
typedef int EdgeType;

typedef struct MGNode {
    int vexnum, arcnum;
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int degree[MaxVertexNum];
} MGNode, *MGraph;

bool visited[MaxVertexNum];

MGraph CreateGraph();
MGraph BuildGraph();
void DFS(MGraph G, int v);
bool CheckG(MGraph G);

int main()
{
    MGraph G = BuildGraph();
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

MGraph CreateGraph()
{
    MGraph G = (MGraph) malloc(sizeof(struct MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        G->degree[v] = 0;
        visited[v] = false;
    }

    return G;
}

MGraph BuildGraph()
{
    MGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        G->edge[v - 1][w - 1] = 1;
        G->edge[w - 1][v - 1] = 1;
        G->degree[v - 1]++;
        G->degree[w - 1]++;
    }
    return G;
}

void DFS(MGraph G, int v)
{
    visited[v] = true;
    for (int w = 0; w < G->vexnum; w++) {
        if (!visited[w] && G->edge[v][w]) {
            DFS(G, w);
        }
    }
}

bool CheckG(MGraph G)
{
    for (int v = 0; v < G->vexnum; v++)
        if (G->degree[v] % 2 == 1)
            return false;
    return true;
}

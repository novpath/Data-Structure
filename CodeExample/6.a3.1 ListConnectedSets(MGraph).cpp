#include <cstdio>
#include <stdlib.h>

#define NULL nullptr
#define MaxVertexNum 100

typedef struct MGNode {
    int vexnum, arcnum;
    int edge[MaxVertexNum][MaxVertexNum];
} MGNode, *MGraph;

MGraph BuildGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G->edge[i][j] = 0;
        }
    }
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        G->edge[v][w] = 1;
        G->edge[w][v] = 1;
    }
    return G;
}

bool Visited[MaxVertexNum];

void DFS(MGraph G, int v)
{
    printf("%d ", v);
    Visited[v] = true;
    for (int w = 0; w < G->vexnum; w++) {
        if (!Visited[w] && G->edge[v][w]) {
            DFS(G, w);
        }
    }
}

void DFSTraverse(MGraph G)
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

void BFS(MGraph G, int v)
{
    Queue Q;
    int front = 0, rear = 0;
    Q[rear++] = v;
    printf("%d ", v);
    Visited[v] = true;
    while (front != rear) {
        v = Q[front++];
        for (int w = 0; w < G->vexnum; w++) {
            if (!Visited[w] && G->edge[v][w] == 1) {
                printf("%d ", w);
                Visited[w] = true;
                Q[rear++] = w;
            }
        }
    }
}

void BFSTraverse(MGraph G)
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
    MGraph G = BuildGraph();
    DFSTraverse(G);
    BFSTraverse(G);

    free(G);
    return 0;
}

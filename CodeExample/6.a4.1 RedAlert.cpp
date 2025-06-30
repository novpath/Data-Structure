#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxCityNum 500

typedef struct MGNode {
    int vexnum, arcnum;
    int edge[MaxCityNum][MaxCityNum];
} MGNode, *MGraph;

bool visited[MaxCityNum];
bool Capture[MaxCityNum] = {false,};

MGraph BuildGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        for (int w = 0; w < G->vexnum; w++) {
            G->edge[v][w] = 0;
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

void DFS(MGraph G, int v)
{
    visited[v] = true;
    for (int w = 0; w < G->vexnum; w++) {
        if (!Capture[w] && !visited[w] && G->edge[v][w]) {
            DFS(G, w);
        }
    }
}

int DFSTraverse(MGraph G)
{
    for (int v = 0; v < G->vexnum; v++)
        visited[v] = false;
    int cnt = 0;
    for (int v = 0; v < G->vexnum; v++) {
        if (!visited[v] && !Capture[v]) {
            cnt++;
            DFS(G, v);
        }
    }
    return cnt;
}

void CaptureCity(MGraph G)
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int connected = DFSTraverse(G);
        int city;
        scanf("%d", &city);
        Capture[city] = true;
        for (int j = 0; j < G->vexnum; j++) {
            G->edge[city][j] = 0;
            G->edge[j][city] = 0;
        }
        int new_connected = DFSTraverse(G);
        if (new_connected <= connected) {
            printf("City %d is lost.\n", city);
        } else {
            printf("Red Alert: City %d is lost!\n", city);
        }
    }
    if (n == G->vexnum)
        printf("Game Over.\n");
}

int main()
{
    MGraph G = BuildGraph();
    CaptureCity(G);

    free(G);
    return 0;
}

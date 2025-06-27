#include <cstdio>
#include <cstring>
#include <cstdlib>

#define NULL nullptr

#define MaxVertexNum 500
#define INFINITY 65535
typedef int VertexType;
typedef int WeightType;

typedef struct MGNode {
    int vexnum, arcnum;
    WeightType dist[MaxVertexNum][MaxVertexNum];
    WeightType cost[MaxVertexNum][MaxVertexNum];
    VertexType s, d;
} MGNode, *MGraph;

MGraph CreateGraph();
MGraph BuildGraph();

VertexType FindVertex(MGraph graph, int dist[], int collected[]);
void Dijkstra(MGraph graph, int dist[], int cost[], VertexType s);

int main()
{
    MGraph G = BuildGraph();
    int *dist = (int *) malloc(sizeof(int) * G->vexnum);
    int *cost = (int *) malloc(sizeof(int) * G->vexnum);
    if (dist == NULL || cost == NULL)
        return -1;
    Dijkstra(G, dist, cost, G->s);
    printf("%d %d\n", dist[G->d], cost[G->d]);

    free(dist);
    free(cost);
    free(G);
    return 0;
}

MGraph CreateGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    scanf("%d %d", &G->s, &G->d);
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G->dist[i][j] = INFINITY;
            G->cost[i][j] = INFINITY;
        }
    }
    return G;
}

MGraph BuildGraph()
{
    MGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w, dist, cost;
        scanf("%d %d %d %d", &v, &w, &dist, &cost);
        G->cost[v][w] = G->cost[w][v] = cost;
        G->dist[v][w] = G->dist[w][v] = dist;
    }
    return G;
}

void Dijkstra(MGraph G, int dist[], int cost[], VertexType s)
{
    bool collected[G->vexnum];
    for (VertexType v = 0; v < G->vexnum; v++) {
        dist[v] = G->dist[s][v];
        cost[v] = G->cost[s][v];
        collected[v] = false;
    }
    dist[s] = cost[s] = 0;
    while (true) {
        VertexType v = -1;
        for (VertexType w = 0; w < G->vexnum - 1; w++) {
            if (!collected[w] && (v == -1 || dist[w] < dist[v]))
                v = w;
        }
        if (v == -1 || dist[v] == INFINITY)
            break;
        collected[v] = true;
        for (VertexType w = 0; w < G->vexnum; w++) {
            if (dist[v] + G->dist[v][w] < dist[w]) {
                dist[w] = dist[v] + G->dist[v][w];
                cost[w] = cost[v] + G->cost[v][w];
            } else if (dist[v] + G->dist[v][w] == dist[w] && cost[v] + G->cost[v][w] < cost[w]) {
                cost[w] = cost[v] + G->cost[v][w];
            }
        }
    }
}

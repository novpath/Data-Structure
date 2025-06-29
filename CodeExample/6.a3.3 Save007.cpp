#include <cstdio>
#include <cstdlib>
#include <cmath>

#define NULL nullptr
#define MaxVertexNum 100
bool Visited[MaxVertexNum];

typedef struct GNode {
    int vexnum;
    double d;
    int x[MaxVertexNum];
    int y[MaxVertexNum];
} GNode, *Graph;

bool answer = false;

bool DFS(Graph G, int v)
{
    Visited[v] = true;
    if (G->x[v] + G->d >= 50 || G->y[v] + G->d >= 50 || G->x[v] - G->d <= -50 || G->y[v] - G->d <= -50)
        answer = true;
    for (int w = 0; w < G->vexnum; w++) {
        if (!Visited[w] && G->d >= sqrt(pow((G->x[w] - G->x[v]), 2) + pow((G->y[w] - G->y[v]), 2))) {
            answer = DFS(G, w);
            if (answer == true)
                break;
        }
    }
    return answer;
}

void Save007(Graph G)
{
    for (int v = 0; v < G->vexnum; v++)
        Visited[v] = false;
    for (int v = 0; v < G->vexnum; v++) {
        if (!Visited[v] && (G->d + 7.5) >= sqrt(pow(G->x[v], 2) + pow(G->y[v], 2))) {
            answer = DFS(G, v);
            if (answer) break;
        }
    }
    printf("%s\n", answer ? "Yes" : "No");
}


int main()
{
    Graph G = (Graph) malloc(sizeof(struct GNode));
    scanf("%d %lf", &G->vexnum, &G->d);
    for (int i = 0; i < G->vexnum; i++) {
        scanf("%d %d", &G->x[i], &G->y[i]);
    }
    Save007(G);

    free(G);
    return 0;
}

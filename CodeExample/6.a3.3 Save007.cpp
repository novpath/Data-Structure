#include <cstdio>
#include <cstdlib>
#include <cmath>

#define NULL nullptr
#define MaxVertexNum 100
bool Visited[MaxVertexNum];

typedef struct point {
    int x;
    int y;
} point;

typedef struct GNode {
    int vexnum;
    double d;
    point pt[MaxVertexNum];
} GNode, *Graph;

bool answer = false;

bool DFS(Graph G, int v)
{
    Visited[v] = true;
    if (abs(G->pt[v].x) + G->d >= 50 || abs(G->pt[v].y) + G->d >= 50)
        answer = true;
    for (int w = 0; w < G->vexnum; w++) {
        if (!Visited[w] && G->d >= sqrt(
                pow((G->pt[w].x - G->pt[v].x), 2) + pow((G->pt[w].y - G->pt[v].y), 2))) {
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
        if (!Visited[v] && (G->d + 7.5) >= sqrt(pow(G->pt[v].x, 2) + pow(G->pt[v].y, 2))) {
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
        scanf("%d %d", &G->pt[i].x, &G->pt[i].y);
    }
    Save007(G);

    free(G);
    return 0;
}

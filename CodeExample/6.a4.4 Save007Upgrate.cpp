#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#define NULL nullptr
#define MaxVertexNum 101
#define IslandRadius 7.5
#define BOUNDARY 50
#define INF 0x3f3f3f3f

int dist[MaxVertexNum];
int pre[MaxVertexNum];

typedef int Queue[MaxVertexNum];

typedef struct point {
    int x;
    int y;
    double first;
} point;

typedef struct GNode {
    int vexnum;
    double d;
    point pt[MaxVertexNum];
} GNode, *Graph;

bool IsSafe(Graph G, int w)
{
    return (abs(G->pt[w].x) + G->d >= BOUNDARY || abs(G->pt[w].y) + G->d >= BOUNDARY);
}

bool Jump(Graph G, int v, int w)
{
    return (pow(G->pt[v].x - G->pt[w].x, 2) + pow(G->pt[v].y - G->pt[w].y, 2) <= pow(G->d, 2));
}

void BFS(Graph G)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(pre, -1, sizeof(pre));
    Queue Q;
    int front = 0, rear = 0;
    for (int v = 0; v < G->vexnum; v++) {
        if (G->pt[v].first > 0 && G->pt[v].first <= G->d) {
            Q[rear++] = v;
            dist[v] = 1;
            pre[v] = -1;
        }
    }
    while (front != rear) {
        int v = Q[front++];
        if (dist[G->vexnum] == INF && IsSafe(G, v)) {
            dist[G->vexnum] = dist[v] + 1;
            pre[G->vexnum] = v;
            break;
        }
        for (int w = 0; w < G->vexnum; w++) {
            if (dist[w] == INF && Jump(G, v, w)) {
                Q[rear++] = w;
                dist[w] = dist[v] + 1;
                pre[w] = v;
            }
        }
    }
}

int Cmp(const void *a, const void *b)
{
    // 将 void 指针转换为结构体指针
    const point *pa = (const point *) a;
    const point *pb = (const point *) b;

    // 比较 double 值并返回结果（避免直接相减导致的精度问题）
    if (pa->first < pb->first) return -1;
    if (pa->first > pb->first) return 1;
    return 0;
}

void PrintPath(Graph G, int end, const int pre[])
{
    int path[G->vexnum + 1];
    int len = 0;
    int cur = end;
    while (cur != -1) {
        path[len++] = cur;
        cur = pre[cur];
    }
    for (int i = len - 1; i; i--) {   // 四周岸边虚拟终点不需要打印
        printf("%d %d\n", G->pt[path[i]].x, G->pt[path[i]].y);
    }
}

int main()
{
    Graph G = (Graph) malloc(sizeof(struct GNode));
    scanf("%d %lf", &G->vexnum, &G->d);
    if (G->d + IslandRadius >= BOUNDARY) {
        printf("1\n");
        return 0;
    }
    for (int i = 0; i < G->vexnum; i++) {
        scanf("%d %d", &G->pt[i].x, &G->pt[i].y);
        G->pt[i].first = sqrt(pow(G->pt[i].x, 2) + pow(G->pt[i].y, 2)) - IslandRadius;
    }
    qsort(G->pt, G->vexnum, sizeof(G->pt[0]), Cmp);
    BFS(G);
    if (dist[G->vexnum] == INF) {
        printf("0\n");
    } else {
        printf("%d\n", dist[G->vexnum]);
        PrintPath(G, G->vexnum, pre);
    }

    free(G);
    return 0;
}

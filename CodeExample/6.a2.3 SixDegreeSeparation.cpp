#include <cstdio>

#define MaxVertex 1001

typedef struct MGraph {
    int vexnum, arcnum;
    int edge[MaxVertex][MaxVertex];
    int vertex[MaxVertex];
} MGraph;

int visited[MaxVertex];

void InitializeVisited(int vexnum)
{
    for (int i = 1; i <= vexnum; i++)
        visited[i] = false;
}

typedef int Queue[MaxVertex];

int BFS(const MGraph &G, int v)
{
    visited[v] = true;
    int cnt = 1;
    int level = 0, last = v, tail = -1;
    Queue Q;
    int front = 0, rear = 0;
    Q[rear++] = v;
    while (front != rear) {
        v = Q[front++];
        for (int w = 1; w <= G.vexnum; w++) {
            if (!visited[w] && G.edge[v][w] == 1) {
                visited[w] = true;
                cnt++;
                tail = w;
                Q[rear++] = w;
            }
        }
        if (v == last) {
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return cnt;
}

void SDS(const MGraph &G)
{
    for (int v = 1; v <= G.vexnum; v++) {
        InitializeVisited(G.vexnum);
        int count = BFS(G, v);
        printf("%d: %.2f%%\n", v, 100 * (double) count / (double) G.vexnum);
    }
}

int main()
{
    MGraph G;
    scanf("%d %d", &G.vexnum, &G.arcnum);
    for (int i = 1; i <= G.arcnum; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        G.edge[x][y] = 1;
        G.edge[y][x] = 1;
    }
    SDS(G);

    return 0;
}

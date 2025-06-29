#include <cstdio>
#include <cstdlib>

#define MaxCities 500
#define INF 0x3f3f3f3f

typedef struct MGNode {
    int N, M;
    int S, D;
    int team[MaxCities];              // 各城市救援队数量
    int dist[MaxCities][MaxCities];   // 邻接矩阵存储道路长度
} MGNode, *MGraph;

int dist[MaxCities];              // 起点到各点的最短距离
int teams[MaxCities];             // 起点到各点的最大救援队数量
int pathCount[MaxCities];         // 起点到各点的最短路径数量
int pre[MaxCities];               // 路径前驱节点
bool visited[MaxCities] = {false};// 节点访问标记

MGraph BuildGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d %d %d", &G->N, &G->M, &G->S, &G->D);
    // 读取各城市救援队数量
    for (int i = 0; i < G->N; i++) {
        scanf("%d", &G->team[i]);
    }
    // 初始化邻接矩阵
    for (int i = 0; i < G->N; i++) {
        for (int j = 0; j < G->N; j++) {
            G->dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    // 读取道路信息
    for (int i = 0; i < G->M; i++) {
        int u, v, length;
        scanf("%d %d %d", &u, &v, &length);
        G->dist[u][v] = length;     // 无向图，双向赋值
        G->dist[v][u] = length;
    }
    return G;
}

void Dijkstra(MGraph G, int s)
{
    // 初始化数组
    for (int i = 0; i < G->N; i++) {
        dist[i] = INF;
        teams[i] = 0;
        pathCount[i] = 0;
        pre[i] = -1;
    }
    // 起点初始化
    dist[G->S] = 0;
    teams[G->S] = G->team[G->S];
    pathCount[G->S] = 1;

    while (true) {
        // 寻找未访问节点中距离最小的节点
        int v = -1;
        for (int w = 0; w < G->N; w++) {
            if (!visited[w] && (v == -1 || dist[w] < dist[v])) {
                v = w;
            }
        }
        // 所有可达节点已处理完毕
        if (v == -1) break;
        visited[v] = true;
        // 更新邻接节点
        for (int w = 0; w < G->N; w++) {
            if (!visited[w] && G->dist[v][w] != INF) {
                int newDist = dist[v] + G->dist[v][w];
                // 找到更短路径
                if (newDist < dist[w]) {
                    dist[w] = newDist;
                    teams[w] = teams[v] + G->team[w];
                    pathCount[w] = pathCount[v];
                    pre[w] = v;
                }
                // 路径长度相等
                else if (newDist == dist[w]) {
                    pathCount[w] += pathCount[v]; // 累加路径数量
                    // 更新救援队数量更大的路径
                    if (teams[v] + G->team[w] > teams[w]) {
                        teams[w] = teams[v] + G->team[w];
                        pre[w] = v;
                    }
                }
            }
        }
    }
}

int main()
{
    MGraph G = BuildGraph();
    Dijkstra(G, G->S);
    printf("%d %d\n", pathCount[G->D], teams[G->D]);

    // 回溯路径
    int path[MaxCities];
    int cur = G->D;
    int count = 0;
    while (cur != G->S) {
        path[count++] = cur;
        cur = pre[cur];
    }
    path[count++] = G->S;

    // 反向输出路径
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" ");
    }

    free(G);
    return 0;
}

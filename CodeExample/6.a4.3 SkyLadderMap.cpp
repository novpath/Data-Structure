#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 500
#define INF 0x3f3f3f3f

typedef struct MGNode {
    int vexnum, arcnum;
    int dist[MaxVertexNum][MaxVertexNum];  // 存储距离
    int time[MaxVertexNum][MaxVertexNum];  // 存储时间
} MGNode, *MGraph;

MGraph BuildGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    // 初始化距离和时间矩阵
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G->dist[i][j] = (i == j ? 0 : INF);
            G->time[i][j] = (i == j ? 0 : INF);
        }
    }
    // 读入道路信息
    for (int i = 0; i < G->arcnum; i++) {
        int v1, v2, one_way, length, time;
        scanf("%d %d %d %d %d", &v1, &v2, &one_way, &length, &time);
        G->dist[v1][v2] = length;
        G->time[v1][v2] = time;
        if (!one_way) {
            G->dist[v2][v1] = length;
            G->time[v2][v1] = time;
        }
    }
    return G;
}

// Dijkstra 算法实现（通用版本）
void Dijkstra(MGraph G, int s, int flag, int prior[], int minor[], int pre[])
{
    bool visited[MaxVertexNum] = {false};  // 访问标记数组
    // 初始化第一权重、第二权重和前驱
    for (int i = 0; i < G->vexnum; i++) {
        prior[i] = INF;
        minor[i] = INF;
        pre[i] = -1;
    }
    prior[s] = 0;
    minor[s] = 0;
    while (true) {
        // 找到未访问的最小代价节点
        int v = -1;
        for (int w = 0; w < G->vexnum; w++) {
            if (!visited[w] && (v == -1 || (prior[w] < prior[v]) || (
                                    prior[w] == prior[v] && minor[w] < minor[v]))) {
                v = w;
            }
        }
        if (v == -1) break;  // 所有节点已访问
        visited[v] = true;
        for (int w = 0; w < G->vexnum; w++) {       // 遍历所有邻接点
            if (visited[w]) continue;
            // 跳过不存在的边
            if (flag == 0 && G->time[v][w] == INF) continue;
            if (flag == 1 && G->dist[v][w] == INF) continue;
            // 根据 flag 确定主要权重和次要权重
            int primary_weight, minor_weight;
            if (flag == 0) {  // 最快路线：时间为主，距离为次
                primary_weight = G->time[v][w];
                minor_weight = G->dist[v][w];
            } else {  // 最短距离：距离为主，边数为次
                primary_weight = G->dist[v][w];
                minor_weight = 1;  // 每条边计数为1
            }

            int new_prior = prior[v] + primary_weight;
            int new_minor = minor[v] + minor_weight;
            if (new_prior < prior[w] || (new_prior == prior[w] && new_minor < minor[w])) {
                prior[w] = new_prior;
                minor[w] = new_minor;
                pre[w] = v;
            }
        }
    }
}

void GetPath(int end, int pre[], int path[], int *path_len)
{
    int len = 0;
    int cur = end;
    while (cur != -1) {
        path[len++] = cur;
        cur = pre[cur];
    }
    *path_len = len;
}

int IsSamePath(int path1[], int len1, int path2[], int len2)
{
    if (len1 != len2) return 0;
    for (int i = 0; i < len1; i++) {
        if (path1[i] != path2[i]) return 0;
    }
    return 1;
}

int main()
{
    MGraph G = BuildGraph();
    int s, d;
    scanf("%d %d", &s, &d);
    // 存储路径结果的数组
    int primary[MaxVertexNum], minor[MaxVertexNum], pre[MaxVertexNum], path_time[MaxVertexNum], path_dist[MaxVertexNum];
    // 计算最快路线(flag = 0)
    Dijkstra(G, s, 0, primary, minor, pre);
    int len_time = 0, time_priority = primary[d];
    GetPath(d, pre, path_time, &len_time);
    // 计算最短距离路线(flag = 1)
    Dijkstra(G, s, 1, primary, minor, pre);
    int len_dist = 0, dist_priority = primary[d];
    GetPath(d, pre, path_dist, &len_dist);
    // 检查路径是否相同并输出结果
    if (IsSamePath(path_time, len_time, path_dist, len_dist)) {
        printf("Time = %d; Distance = %d: ", time_priority, dist_priority);
        for (int i = len_time - 1; i >= 0; i--)
            printf("%d%s", path_time[i], i != 0 ? " => " : "\0");
    } else {
        printf("Time = %d: ", time_priority);
        for (int i = len_time - 1; i >= 0; i--) {
            printf("%d%s", path_time[i], i != 0 ? " => " : "\n");
        }
        printf("Distance = %d: ", dist_priority);
        for (int i = len_dist - 1; i >= 0; i--) {
            printf("%d%s", path_dist[i], i != 0 ? " => " : "\0");
        }
    }

    free(G);

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NULL nullptr
#define MaxVexNum 1001
using namespace std;

typedef struct ArcNode {    // 邻接表节点
    int adjvex;             // 邻接顶点索引
    struct ArcNode *nextarc;// 下一条边指针
} ArcNode;

typedef struct VNode {      // 顶点节点
    int data;               // 顶点数据（未使用）
    ArcNode *firstarc;      // 第一条邻接边
} VNode, AdjList[MaxVexNum];

typedef struct ALGNode {    // 图结构
    int vexnum, arcnum;     // 顶点数和边数
    AdjList vertices;       // 邻接表
} ALGNode, *ALGraph;

void AddEdge(ALGraph G, int v, int w)   // 添加无向边
{
    // 添加 v->w 的边
    ArcNode *arc_vw = (ArcNode *) malloc(sizeof(ArcNode));
    arc_vw->adjvex = w;
    arc_vw->nextarc = G->vertices[v].firstarc;
    G->vertices[v].firstarc = arc_vw;
    // 添加 w->v 的边
    ArcNode *arc_wv = (ArcNode *) malloc(sizeof(ArcNode));
    arc_wv->adjvex = v;
    arc_wv->nextarc = G->vertices[w].firstarc;
    G->vertices[w].firstarc = arc_wv;
}

ALGraph BuildGraph()    // 构建图
{
    ALGraph G = (ALGraph) malloc(sizeof(ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    // 初始化邻接表
    for (int v = 0; v < G->vexnum; v++) {
        G->vertices[v].firstarc = NULL;
    }
    // 添加边（输入编号从 1 开始，转换为 0 开始）
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        v--;
        w--;             // 转换为 0-based 索引
        AddEdge(G, v, w);
    }
    return G;
}

void FreeGraph(ALGraph G)    // 释放图内存
{
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    free(G);
}

typedef int Queue[MaxVexNum];

double BFS(ALGraph G, int s)    // 计算单个结点的紧密度中心性
{
    int dist[MaxVexNum];        // 存储最短距离
    memset(dist, -1, sizeof(dist));  // 初始化为 -1（未访问）
    Queue Q;
    int front = 0, rear = 0;
    Q[rear++] = s;
    dist[s] = 0;
    int cnt = 1;            // 访问结点计数
    long sum_dist = 0;      // 距离总和（防溢出）
    while (front != rear) {
        int v = Q[front++];
        for (ArcNode *p = G->vertices[v].firstarc; p != NULL; p = p->nextarc) {
            int w = p->adjvex;
            if (dist[w] == -1) {      // 未访问
                dist[w] = dist[v] + 1;
                sum_dist += dist[w];  // 累加距离
                cnt++;
                Q[rear++] = w;
            }
        }
    }
    // 非连通图返回 0
    if (cnt != G->vexnum) return 0.0;
    // 计算紧密度中心性
    return (G->vexnum - 1) * 1.0 / sum_dist;
}

int main()
{
    ALGraph G = BuildGraph();
    int k;                           // 读取查询结点
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {    // 计算并输出结果
        int nodes;
        scanf("%d", &nodes);
        double closeness = BFS(G, nodes - 1);
        printf("Cc(%d)=%.2f%c", nodes, closeness, i == k - 1 ? '\0' : '\n');  // 输出时转回 1-based
    }

    FreeGraph(G);          // 释放边表结点和图
    return 0;
}

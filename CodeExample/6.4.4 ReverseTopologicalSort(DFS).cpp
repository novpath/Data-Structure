#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxSize 100

typedef int VertexType;

typedef struct ArcNode {
    int adjvex;
    ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxSize];

typedef struct {
    AdjList vertices;
    int vexnum;
    int arcnum;
} ALGraph;

typedef struct {
    int data[MaxSize];      // 栈数据
    int top;                // 栈顶指针
} Stack;

ALGraph CreateALGraph();
void printAdjList(const ALGraph &G);
void DestroyGraph(ALGraph &G);

int visited[MaxSize];

void DFS(const ALGraph &G, int v)
{   // 从顶点 v 出发,深度优先遍历图 G
    visited[v] = true;              // 设已访问标记
    for (ArcNode *p = G.vertices[v].firstarc; p != NULL; p = p->nextarc) {
        int neighbor = p->adjvex;
        if (!visited[neighbor]) {          // neighbor 为 v 的尚未访问的邻接顶点
            DFS(G, neighbor);
        }
    }
    printf("%d ", v);
}

void DFSTraverse(const ALGraph &G, int &cnt)
{                                      // 对图 G 进行深度优先遍历
    for (int i = 0; i < G.vexnum; ++i) visited[i] = false;             // 初始化已访问标记数据
    for (int i = 0; i < G.vexnum; ++i)  // 本代码中是从 i = 0 开始遍历
        if (!visited[i])
            DFS(G, i);
}

int main()
{
    // 创建测试图
    ALGraph G = CreateALGraph();
    printf("Adjacency List:\n");
    printAdjList(G);
    // 初始化 visit 数组
    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    // 执行逆拓扑排序
    int cnt = 0;
    DFSTraverse(G, cnt);

    // 释放图内存
    DestroyGraph(G);
    return 0;
}

ALGraph CreateALGraph()
{
    ALGraph G;
    printf("Input the number of vertices and edges:\n");

    scanf("%d %d", &G.vexnum, &G.arcnum);
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = i;
        G.vertices[i].firstarc = NULL;
    }

    for (int i = 0; i < G.arcnum; i++) {
        int x, y;
        printf("Add edge x to y:\n");
        scanf("%d %d", &x, &y);
        // 添加 x->y 的边
        ArcNode *arc_xy = (ArcNode *) malloc(sizeof(ArcNode));
        arc_xy->adjvex = y;
        arc_xy->nextarc = G.vertices[x].firstarc;
        G.vertices[x].firstarc = arc_xy;
    }

    return G;
}

void printAdjList(const ALGraph &G)
{
    for (int i = 0; i < G.vexnum; ++i) {
        printf("Vertex %d's neighbor:", G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            printf(" %d", G.vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

void DestroyGraph(ALGraph &G)
{
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G.vertices[i].firstarc = NULL;
    }
}


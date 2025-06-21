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
} VNode;

typedef struct {
    VNode *vertices;
    int vexnum;
    int arcnum;
} ALGraph;

typedef struct {
    int data[MaxSize];      // 栈数据
    int top;                // 栈顶指针
} Stack;

ALGraph *CreateALGraph();
void printAdjList(const ALGraph *G);
void DestroyGraph(ALGraph *G);
void InitStack(Stack &S);
bool Push(Stack &S, int e);
bool Pop(Stack &S, int &e);
bool IsEmpty(const Stack &S);

int print[MaxSize];           // 记录拓扑排序序列
int indegree[MaxSize];        // 记录每个顶点的出度

bool ReverseTopologicalSort(const ALGraph &G)
{
    // 1. 初始化栈并添加所有入度为 0 的顶点
    Stack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; i++) {
        if (indegree[i] == 0)
            Push(S, i);
    }
    // 2. 拓扑排序主循环
    int count = 0;
    while (!IsEmpty(S)) {
        int u;
        Pop(S, u);
        print[count++] = u;                   // 将顶点加入拓扑序列
        ArcNode *p = G.vertices[u].firstarc;  // 遍历顶点 v 的所有后继（通过邻接表）
        while (p != NULL) {
            int v = p->adjvex;                // u 是 v 的后继
            if (--indegree[v] == 0) {         // 减少后继 u 的入度，若为 0 则入栈
                Push(S, v);
            }
            p = p->nextarc;
        }
    }
    // 3. 检查是否存在环
    if (count < G.vexnum)
        return false;     // 有环，排序失败
    return true;          // 否则，排序成功
}

int main()
{
    // 创建测试图
    ALGraph *G = CreateALGraph();
    printf("Adjacency List:\n");
    printAdjList(G);
    // 初始化入度数组和 print 数组
    for (int i = 0; i < G->vexnum; i++) {
        print[i] = -1;
        for (ArcNode *p = G->vertices[i].firstarc; p != NULL; p = p->nextarc)
            indegree[p->adjvex]++;            // 更新入度
    }
    // 执行拓扑排序
    if (ReverseTopologicalSort(*G)) {
        printf("Topological Sort Sequence:");
        for (int i = 0; i < G->vexnum; i++)
            printf(" %d", print[i]);
        printf("\n");
    } else {
        printf("Graph Exists Ring!\n");
    }

    // 释放图内存
    DestroyGraph(G);
    return 0;
}

ALGraph *CreateALGraph()
{
    ALGraph *G = (ALGraph *) malloc(sizeof(ALGraph));
    printf("Input the number of vertices and edges:\n");

    scanf("%d %d", &G->vexnum, &G->arcnum);
    G->vertices = (VNode *) malloc(G->vexnum * sizeof(VNode));
    for (int i = 0; i < G->vexnum; i++) {
        G->vertices[i].data = i;
        G->vertices[i].firstarc = NULL;
    }

    for (int i = 0; i < G->arcnum; i++) {
        int x, y;
        printf("Add edge x to y:\n");
        scanf("%d %d", &x, &y);
        // 添加 x->y 的边
        ArcNode *arc_xy = (ArcNode *) malloc(sizeof(ArcNode));
        arc_xy->adjvex = y;
        arc_xy->nextarc = G->vertices[x].firstarc;
        G->vertices[x].firstarc = arc_xy;
    }

    return G;
}

void printAdjList(const ALGraph *G)
{
    if (G == NULL || G->vertices == NULL)
        return;
    for (int i = 0; i < G->vexnum; ++i) {
        printf("Vertex %d's neighbor:", G->vertices[i].data);
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            printf(" %d", G->vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

void DestroyGraph(ALGraph *G)
{
    if (G == NULL || G->vertices == NULL)
        return;
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G->vertices[i].firstarc = NULL;
    }
    free(G->vertices);
    free(G);
}

void InitStack(Stack &S)
{
    S.top = -1;
}

bool Push(Stack &S, int e)
{
    if (S.top >= MaxSize - 1) return false;
    S.data[++S.top] = e;
    return true;
}

bool Pop(Stack &S, int &e)
{
    if (S.top == -1) return false;
    e = S.data[S.top--];
    return true;
}

bool IsEmpty(const Stack &S)
{
    return S.top == -1;
}

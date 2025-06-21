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

int print[MaxSize];            // 记录逆拓扑排序序列
int outdegree[MaxSize];        // 记录每个顶点的出度

ALGraph *ALGraphToInvALGraph(const ALGraph *G)    // 将图的邻接表转化为逆邻接表
{
    if (G == NULL || G->vertices == NULL)
        return NULL;
    ALGraph *invG = (ALGraph *) malloc(sizeof(ALGraph));
    invG->arcnum = G->arcnum;                         // 初始化逆邻接表的边数目
    invG->vexnum = G->vexnum;                         // 初始化逆邻接表的顶点数目
    invG->vertices = (VNode *) malloc(sizeof(VNode) * invG->vexnum);
    for (int i = 0; i < invG->vexnum; i++) {
        invG->vertices[i].data = G->vertices[i].data; // 初始化逆邻接表的顶点信息
        invG->vertices[i].firstarc = NULL;            // 初始化指向第一条依附该顶点的弧的指针
    }
    for (int i = 0; i < invG->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;           // 取得指向第一条依附该顶点的弧的指针
        while (p != NULL) {                             // 遍历邻接表中第 i 个顶点所有邻接边
            int neighbor = p->adjvex;
            ArcNode *s = (ArcNode *) malloc(sizeof(ArcNode));
            s->adjvex = i;
            s->nextarc = invG->vertices[neighbor].firstarc; // 头插法将顶点 i 挂到 invG.vertices[neighbor] 的边表中
            invG->vertices[neighbor].firstarc = s;
            p = p->nextarc;                                 // 继续往后遍历边表
        }
    }
    return invG;
}

bool ReverseTopologicalSort(const ALGraph &G)
{
    // 1. 初始化栈并添加所有出度为 0 的顶点
    Stack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; i++) {
        if (outdegree[i] == 0)
            Push(S, i);
    }
    // 2. 逆拓扑排序主循环
    int count = 0;
    while (!IsEmpty(S)) {
        int u;
        Pop(S, u);
        print[count++] = u;                   // 将顶点加入逆拓扑序列
        ArcNode *p = G.vertices[u].firstarc;  // 遍历顶点 v 的所有前驱（通过逆邻接表）
        while (p != NULL) {
            int v = p->adjvex;                // v 是 u 的前驱
            if (--outdegree[v] == 0) {        // 减少前驱 v的出度，若为 0 则入栈
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
    // 初始化出度数组和 print 数组
    for (int i = 0; i < G->vexnum; i++) {
        print[i] = -1;
        for (ArcNode *p = G->vertices[i].firstarc; p != NULL; p = p->nextarc)
            outdegree[i]++;            // 更新出度
    }
    // 转换为逆邻接表
    ALGraph *invG = ALGraphToInvALGraph(G);
    printf("Inverse Adjacency List:\n");
    printAdjList(invG);
    // 执行逆拓扑排序
    if (ReverseTopologicalSort(*invG)) {
        printf("Reverse Topological Sort Sequence:");
        for (int i = 0; i < G->vexnum; i++)
            printf(" %d", print[i]);
        printf("\n");
    } else {
        printf("Graph Exists Ring!\n");
    }

    // 释放图内存
    DestroyGraph(G);
    DestroyGraph(invG);
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

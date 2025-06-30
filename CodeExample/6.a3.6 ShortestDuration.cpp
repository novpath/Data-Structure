#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxVertexNum 100

typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    int ve;        // 最早开始时间
    int data;
    struct ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct ALGNode {
    int vexnum, arcnum;
    AdjList vertices;
} ALGNode, *ALGraph;

int Indegree[MaxVertexNum] = {0,};   // 入度统计
ALGraph BuildGraph();

typedef struct SNode {
    int top;
    int data[MaxVertexNum];
} SNode, *Stack;

Stack CreateStack();
bool IsStackEmpty(Stack S);
bool Push(Stack S, int x);
int Pop(Stack S);
void InitStack(Stack S);
int max(int a, int b);

int CriticalPath(ALGraph G)         // 关键路径计算（支持多起点多终点）
{
    // 初始化所有节点的最早开始时间
    for (int i = 0; i < G->vexnum; i++)
        G->vertices[i].ve = 0;
    // 1. 初始化栈并添加所有入度为 0 的顶点
    Stack S = CreateStack();
    if (S == NULL)
        return -1;
    for (int i = 0; i < G->vexnum; i++) {
        if (Indegree[i] == 0)
            Push(S, i);
    }
    // 2. 拓扑排序主循环
    int cnt = 0;
    int maxDuration = 0;
    while (!IsStackEmpty(S)) {
        int v = Pop(S);
        cnt++;
        ArcNode *p = G->vertices[v].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            // 最早开始时间为所有前驱最早开始时间 + 任务时间的最大值
            G->vertices[w].ve = max(G->vertices[w].ve, G->vertices[v].ve + p->weight);
            if (--Indegree[w] == 0) {
                Push(S, w);
            }
            p = p->nextarc;
            maxDuration = max(maxDuration, G->vertices[w].ve);
        }
    }
    // 3. 检查是否存在环
    if (cnt < G->vexnum) {
        free(S);
        return -1;  // 有环
    }
    free(S);
    return maxDuration;
}

int main()
{
    ALGraph G = BuildGraph();
    int duration = CriticalPath(G);
    if (duration == -1)
        printf("Impossible");
    else
        printf("%d", duration);
    // 释放图内存
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
    }
    free(G);

    return 0;
}

// 栈操作实现
Stack CreateStack()
{
    Stack S = (Stack) malloc(sizeof(SNode));
    S->top = -1;
    return S;
}

void InitStack(Stack S)
{
    S->top = -1;
}

bool IsStackEmpty(Stack S)
{
    return S->top == -1;
}

bool Push(Stack S, int x)
{
    if (S == NULL || S->top == MaxVertexNum - 1)
        return false;
    S->data[++(S->top)] = x;
    return true;
}

int Pop(Stack S)
{
    if (S == NULL || IsStackEmpty(S))
        return -1;
    return S->data[(S->top)--];
}

// 建图函数
ALGraph BuildGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    // 初始化邻接表
    for (int v = 0; v < G->vexnum; v++) {
        G->vertices[v].firstarc = NULL;
    }
    // 读入边信息
    for (int i = 0; i < G->arcnum; i++) {
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        ArcNode *arc = (ArcNode *) malloc(sizeof(ArcNode));
        arc->adjvex = w;
        arc->weight = weight;
        arc->nextarc = G->vertices[v].firstarc;
        G->vertices[v].firstarc = arc;
        Indegree[w]++;
    }

    return G;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

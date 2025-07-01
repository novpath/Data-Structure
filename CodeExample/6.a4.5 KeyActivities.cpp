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
    int vl;        // 最迟开始时间
    int data;
    struct ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct ALGNode {
    int vexnum, arcnum;
    AdjList vertices;
} ALGNode, *ALGraph;

int Indegree[MaxVertexNum] = {0};   // 入度统计
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
int min(int a, int b);

int CriticalPath(ALGraph G)
{
    // 初始化所有节点的最早开始时间
    for (int i = 0; i < G->vexnum; i++)
        G->vertices[i].ve = 0;
    // 创建拓扑排序栈和结果栈
    Stack S = CreateStack();
    Stack T = CreateStack();  // 用于保存拓扑序列
    if (S == NULL || T == NULL)
        return -1;
    // 将入度为 0 的顶点入栈
    for (int i = 0; i < G->vexnum; i++) {
        if (Indegree[i] == 0)
            Push(S, i);
    }
    // 拓扑排序主循环
    int cnt = 0;
    int maxDuration = 0;
    while (!IsStackEmpty(S)) {
        int v = Pop(S);
        Push(T, v);  // 将顶点保存到拓扑序列栈
        cnt++;
        // 更新后继顶点的最早开始时间
        ArcNode *p = G->vertices[v].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            if (--Indegree[w] == 0) {
                Push(S, w);
            }
            // 更新后继的最早开始时间
            G->vertices[w].ve = max(G->vertices[w].ve, G->vertices[v].ve + p->weight);
            if (G->vertices[w].ve > maxDuration)
                maxDuration = G->vertices[w].ve;
            p = p->nextarc;
        }
    }
    // 检查是否存在环
    if (cnt < G->vexnum) {
        free(S);
        free(T);
        printf("0\n");
        return -1;  // 有环
    }
    // 初始化最迟开始时间为最大值
    for (int i = 0; i < G->vexnum; i++) {
        G->vertices[i].vl = maxDuration;
    }
    // 逆拓扑排序计算最迟开始时间
    while (!IsStackEmpty(T)) {
        int v = Pop(T);
        ArcNode *p = G->vertices[v].firstarc;
        while (p != NULL) {
            int w = p->adjvex;
            // 更新当前顶点的最迟开始时间
            G->vertices[v].vl = min(G->vertices[v].vl, G->vertices[w].vl - p->weight);
            p = p->nextarc;
        }
    }
    // 输出总工期
    printf("%d\n", maxDuration);
    // 输出所有关键活动（按顶点编号从小到大）
    for (int u = 0; u < G->vexnum; u++) {
        ArcNode *p = G->vertices[u].firstarc;
        while (p != NULL) {
            int v = p->adjvex;
            int ae = G->vertices[u].ve;             // 活动最早开始时间
            int al = G->vertices[v].vl - p->weight; // 活动最迟开始时间
            if (ae == al) {                         // 判断是否为关键活动
                printf("%d->%d\n", u + 1, v + 1);  // 顶点编号从 1 开始
            }
            p = p->nextarc;
        }
    }
    free(S);
    free(T);
    return maxDuration;
}

int main()
{
    ALGraph G = BuildGraph();
    CriticalPath(G);
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
    if (S != NULL) {
        S->top = -1;
    }
    return S;
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

ALGraph BuildGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    // 初始化邻接表和入度数组
    for (int v = 0; v < G->vexnum; v++) {
        G->vertices[v].firstarc = NULL;
        Indegree[v] = 0;
    }
    // 读入边信息
    for (int i = 0; i < G->arcnum; i++) {
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        v--;
        w--;      // 顶点编号从 1 开始，转换为 0-based 索引
        // 创建新边 <v, w>
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

int min(int a, int b)
{
    return a < b ? a : b;
}

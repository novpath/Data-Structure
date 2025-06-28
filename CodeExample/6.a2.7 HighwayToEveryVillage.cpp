#include <cstdio>
#include <cstdlib>

#define MaxVertexNum 1000
#define MaxEdgeNum 3000
typedef int VertexType;
typedef int WeightType;

typedef struct ArcNode {
    VertexType adjvex;
    WeightType weight;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct ALGNode {
    AdjList vertices;
    int vexnum, arcnum;
} ALGNode, *ALGraph;

typedef struct ENode {
    VertexType v, w;
    WeightType weight;
} ENode, *Edge;

/* ---------- 最小堆定义 ---------- */
typedef Edge Heap[MaxEdgeNum];
Heap H;
int heap_size;  // 全局堆大小

void InitializeHeap(ALGraph G);
void Swap(Edge *a, Edge *b);
void Down(int u);
Edge GetMin();
/* ---------- 最小堆定义结束 ---------- */

/* ---------- 并查集定义 ---------- */
typedef int SetType[MaxVertexNum];
SetType S;

void InitializeSet(int n);
void Union(int root1, int root2);
int Find(int x);
bool CheckCycle(int v, int w);
/* ---------- 并查集定义结束 ---------- */

ALGraph CreateGraph();
void AddEdge(ALGraph G, int v, int w, int weight);
ALGraph BuildGraph();
int Kruskal(ALGraph G);

int main()
{
    ALGraph G = BuildGraph();
    printf("%d\n", Kruskal(G));
    // 释放图内存
    for (int v = 0; v < G->vexnum; v++) {
        ArcNode *p = G->vertices[v].firstarc;
        while (p) {
            ArcNode *tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    free(G);
    // 释放堆中边内存
    for (int i = 1; i <= heap_size; i++) {
        free(H[i]);
    }
    return 0;
}

ALGraph CreateGraph()
{
    ALGraph G = (ALGraph) malloc(sizeof(ALGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        G->vertices[v].firstarc = nullptr;
    }
    return G;
}

void AddEdge(ALGraph G, int v, int w, int weight)
{
    // 添加 v->w 的边
    ArcNode *arc_vw = (ArcNode *) malloc(sizeof(ArcNode));
    arc_vw->adjvex = w;
    arc_vw->weight = weight;
    arc_vw->nextarc = G->vertices[v].firstarc;
    G->vertices[v].firstarc = arc_vw;
    // 添加 w->v 的边 (无向图)
    ArcNode *arc_wv = (ArcNode *) malloc(sizeof(ArcNode));
    arc_wv->adjvex = v;
    arc_wv->weight = weight;
    arc_wv->nextarc = G->vertices[w].firstarc;
    G->vertices[w].firstarc = arc_wv;
}

ALGraph BuildGraph()
{
    ALGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        AddEdge(G, v - 1, w - 1, weight);        // 顶点编号从 0 开始
    }
    return G;
}

void Swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void Down(int u)
{
    int min = u;
    int left = 2 * u;
    int right = 2 * u + 1;

    if (left <= heap_size && H[left]->weight < H[min]->weight)
        min = left;
    if (right <= heap_size && H[right]->weight < H[min]->weight)
        min = right;

    if (min != u) {
        Swap(&H[u], &H[min]);
        Down(min);
    }
}

void InitializeHeap(ALGraph G)
{
    heap_size = 0;
    // 遍历所有边
    for (int v = 0; v < G->vexnum; v++) {
        for (ArcNode *p = G->vertices[v].firstarc; p; p = p->nextarc) {
            if (v < p->adjvex) {  // 避免重复添加无向图的边 (v < w 时才添加)
                heap_size++;
                H[heap_size] = (Edge) malloc(sizeof(ENode));  // 创建新的堆元素
                H[heap_size]->v = v;
                H[heap_size]->w = p->adjvex;
                H[heap_size]->weight = p->weight;
            }
        }
    }
    // 堆调整
    for (int i = heap_size / 2; i >= 1; i--) {
        Down(i);
    }
}

Edge GetMin()
{
    if (heap_size == 0) return nullptr;
    Edge minEdge = H[1];
    Swap(&H[1], &H[heap_size]);
    heap_size--;
    Down(1);
    return minEdge;
}

void InitializeSet(int n)
{
    for (int i = 0; i < n; i++)
        S[i] = -1;
}

int Find(int x)
{
    if (S[x] < 0) return x;
    return S[x] = Find(S[x]);
}

void Union(int root1, int root2)
{
    if (root1 == root2) return;
    if (S[root2] < S[root1]) {  // root2 的集合更大
        S[root2] += S[root1];
        S[root1] = root2;
    } else {
        S[root1] += S[root2];
        S[root2] = root1;
    }
}

bool CheckCycle(int v, int w)
{
    int root1 = Find(v);
    int root2 = Find(w);
    if (root1 == root2) return false;  // 会形成环
    Union(root1, root2);
    return true;
}

int Kruskal(ALGraph G)
{
    InitializeSet(G->vexnum);
    InitializeHeap(G);
    WeightType total_weight = 0;
    int edgeCnt = 0;
    while (edgeCnt < G->vexnum - 1 && heap_size > 0) {
        Edge e = GetMin();
        if (CheckCycle(e->v, e->w)) {
            total_weight += e->weight;
            edgeCnt++;
        }
        free(e);                    // 释放边内存
    }
    if (edgeCnt < G->vexnum - 1)    // 无法形成最小生成树
        total_weight = -1;

    return total_weight;
}

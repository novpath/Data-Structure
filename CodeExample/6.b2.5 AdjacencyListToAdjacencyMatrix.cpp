#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxVertexNum 100        // 图中顶点数目的最大值
#define INFINITY 65535          // 宏定义常量“无穷”

typedef char VertexType;        // 顶点的数据类型
typedef int EdgeType;           // 带权图中边上权值的数据类型

/* 邻接表定义 */
typedef struct ArcNode {
    int adjvex;                 // 该弧所指向的顶点的位置
    struct ArcNode *nextarc;    // 指向下一条弧的指针
} ArcNode;

typedef struct VNode {
    VertexType data;            // 顶点信息
    ArcNode *firstarc;          // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;           // 邻接表
    int vexnum, arcnum;         // 图的顶点数和弧数
} ALGraph;                      // ALGraph 是以邻接表存储的图类型

/* 邻接矩阵定义 */
typedef struct {
    VertexType Vex[MaxVertexNum];             // 顶点
    EdgeType E[MaxVertexNum][MaxVertexNum];   // 边的权
    int vexnum, arcnum;                       // 图的当前顶点数和弧数
} MGraph;

void initALGraph(ALGraph *G);
ArcNode *createArcNode(int adjvex);
void buildAdjList(ALGraph *G);
void printAdjList(const ALGraph *G);

MGraph *AdjacencyListToAdjacencyMatrix(const ALGraph *G)
{
    MGraph *M = (MGraph *) malloc(sizeof(MGraph));
    M->vexnum = G->vexnum;
    M->arcnum = G->arcnum;
    for (int i = 0; i < G->vexnum; i++)
        M->Vex[i] = G->vertices[i].data;
    for (int i = 0; i < G->vexnum; i++) {
        M->E[i][i] = 0;
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            M->E[i][p->adjvex] = 1;
            p = p->nextarc;
        }
    }
    return M;
}

void printAdjMatrix(const MGraph *G)
{
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            printf("%d%c", G->E[i][j], (j == G->vexnum - 1) ? '\n' : ' ');
        }
    }
}

int main()
{
    /* 测试代码生成 */
    ALGraph graph;
    buildAdjList(&graph);
    printAdjList(&graph);

    MGraph *M = AdjacencyListToAdjacencyMatrix(&graph);
    printAdjMatrix(M);

    free(M);
    return 0;
}

// 邻接矩阵数据
int adjacencyMatrix[5][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 1, 0},
    {1, 1, 1, 0, 1},
    {0, 1, 0, 1, 0}
};

// 初始化邻接表
void initALGraph(ALGraph *G)
{
    for (int i = 0; i < G->vexnum; ++i) {
        G->vertices[i].firstarc = NULL;
    }
}

// 创建邻接表节点
ArcNode *createArcNode(int adjvex)
{
    ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    p->adjvex = adjvex;
    p->nextarc = NULL;
    return p;
}

// 构建邻接表
void buildAdjList(ALGraph *G)
{
    // 初始化邻接表
    G->vexnum = 5;   // 设置顶点数
    G->arcnum = 0;   // 初始化边数
    initALGraph(G);

    // 填充顶点数据
    for (int i = 0; i < G->vexnum; ++i)
        G->vertices[i].data = static_cast<char>(i + '1');   // 顶点编号为'1'到'5'

    // 遍历邻接矩阵，构建邻接表
    for (int i = 0; i < G->vexnum; ++i) {
        for (int j = 0; j < G->vexnum; ++j) {
            if (adjacencyMatrix[i][j] != 0 && i != j) {
                // 创建新节点
                ArcNode *newNode = createArcNode(j);
                if (newNode == NULL) {
                    return;
                }
                // 插入到链表头部
                newNode->nextarc = G->vertices[i].firstarc;
                G->vertices[i].firstarc = newNode;
                G->arcnum++;  // 边数加1
            }
        }
    }
}

// 遍历并打印邻接表
void printAdjList(const ALGraph *G)
{
    printf("Adjacency List:\n");
    for (int i = 0; i < G->vexnum; ++i) {
        printf("Vertex %c's neighbor:", G->vertices[i].data);
        ArcNode *p = G->vertices[i].firstarc;
        while (p != NULL) {
            printf(" %c", G->vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

#include <cstdio>
#include <cstdlib>

#define MaxVertexNum 100   // 最大顶点数设为 100
#define INFINITY 65535     // ∞ 设为双字节无符号整数的最大值
typedef int Vertex;        // 用顶点下标表示顶点，为整型
typedef int WeightType;    // 边的权值设为整型
typedef char DataType;     // 顶点存储的数据类型设为字符型

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;

struct GNode {
    int Nv;          // 顶点数
    int Ne;          // 边数
    WeightType *G;   // 邻接矩阵
    DataType *Data;  // 存顶点的数据
    /* 注意：若顶点无数据，此时 Data[] 可以不用出现 */
};

typedef PtrToGNode MGraph;   // 以邻接矩阵存储的图类型

/* 边的定义 */
typedef struct ENode *PtrToENode;

struct ENode {
    Vertex V1, V2;        // 有向边 <V1, V2>
    WeightType weight;    // 权重
};

typedef PtrToENode Edge;

MGraph CreateGraph(int VertexNum)
{   /* 初始化一个有 VertexNum 个顶点但没有边的图 */

    MGraph Graph = (MGraph) malloc(sizeof(struct GNode));  // 建立图
    Graph->G = (WeightType *) malloc(VertexNum * VertexNum * sizeof(WeightType));
    Graph->Data = (DataType *) malloc(VertexNum * sizeof(DataType));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从 0 开始，到(Graph->Nv - 1) */
    for (Vertex V = 0; V < Graph->Nv; V++)
        for (Vertex W = 0; W < Graph->Nv; W++)
            Graph->G[V * Graph->Nv - V + W] = INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    /* 插入边<V1,V2> */
    Graph->G[E->V1 * (Graph->Nv - 1) + E->V2] = E->weight;
    /* 若是无向图，还要插入边 <v2,v1> */
    Graph->G[E->V2 * (Graph->Nv - 1) + E->V1] = E->weight;
}

MGraph BuildGraph()
{
    int Nv;
    scanf("%d", &Nv);   // 读入顶点个数
    MGraph Graph = CreateGraph(Nv);  // 初始化有 Nv 个顶点但没有边的图

    scanf("%d", &(Graph->Ne));  // 读入边数
    if ((Graph->Ne) != 0) {           // 如果有边
        Edge E = (Edge) malloc(sizeof(struct ENode));  // 建立边结点
        /* 读入边，格式为“起点 终点 权重”，插入邻接矩阵 */
        for (int i = 0; i < Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
    }

    /* 如果顶点有数据的话，读入数据 */
    for (Vertex V = 0; V < Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));

    return Graph;
}

void PrintMGraph(MGraph Graph);

int main()
{
    MGraph Graph = BuildGraph();

    PrintMGraph(Graph);
    free(Graph->G);
    free(Graph->Data);
    free(Graph);
    return 0;
}

void PrintMGraph(MGraph Graph)
{
    for (int i = 0; i < Graph->Nv; i++) {
        for (int j = 0; j < Graph->Nv; j++) {
            if (Graph->G[i * Graph->Nv - i + j] != INFINITY)
                printf("%d ", Graph->G[i * Graph->Nv - i + j]);
            else
                printf("- ");
        }
        printf("\n");
    }
}

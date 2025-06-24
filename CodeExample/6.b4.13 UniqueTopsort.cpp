#include <cstdio>

#define NULL nullptr
#define MAXV 100

typedef char VertexType;
typedef int EdgeType;

typedef struct {
    int numVertices, numEdges; // 图的顶点数和有向边数
    char VerticesList[MAXV];   // 顶点表，MAXV 为已定义常量
    int Edge[MAXV][MAXV];      // 邻接矩阵
} MGraph;

MGraph CreateMGraph();
void printMGraph(const MGraph &G);

int uniquely(MGraph G)
{
    int unique = 1, i, j;
    int indegree[G.numVertices] = {0,};       // 初始化入度表

    for (i = 0; i < G.numVertices; i++)       // 统计各结点的入度
        for (j = 0; j < G.numVertices; j++)
            if (G.Edge[i][j] != 0)
                indegree[j]++;

    for (i = 0; i < G.numVertices; i++) {
        int cnt = 0;
        int source = -1;
        for (j = 0; j < G.numVertices; j++) {  // 统计本轮拓扑排序的起点和个数
            if (indegree[j] == 0) {
                cnt++;
                source = j;
            }
        }
        if (source == -1 || cnt > 1) {         // 没法找到入度为 0 的点(有环)，或者找到多个(拓扑序列不唯一)
            unique = 0;
            break;
        }
        indegree[source] = -1;                 // 本轮入度为 0 的点已处理
        for (j = 0; j < G.numVertices; j++) {  // 邻接点的入度减 1
            if (G.Edge[source][j] != 0)
                indegree[j]--;
        }
    }

    return unique;
}

int main()
{
    // 创建测试图
    MGraph G = CreateMGraph();
    printf("MGraph:\n");
    printMGraph(G);
    printf("%s\n", uniquely(G) ? "uniquely" : "not uniquely");

    return 0;
}

MGraph CreateMGraph()
{
    MGraph G;
    printf("Input the number of vertices:\n");

    scanf("%d", &G.numVertices);
    G.numEdges = G.numVertices;
    for (int i = 0; i < G.numVertices; i++) {
        for (int j = 0; j < G.numVertices; j++) {
            scanf("%d", &G.Edge[i][j]);
        }
    }

    return G;
}

void printMGraph(const MGraph &G)
{
    for (int i = 0; i < G.numVertices; ++i) {
        for (int j = 0; j < G.numVertices; ++j) {
            printf("%d ", G.Edge[i][j]);
        }
        printf("\n");
    }
}


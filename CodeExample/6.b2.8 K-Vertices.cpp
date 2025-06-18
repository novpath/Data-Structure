#include <cstdio>

#define NULL nullptr
#define MAXV 100

typedef struct {                // 图的类型定义
    int numVertices, numEdges;  // 图的顶点数和有向边数
    char VerticesList[MAXV];    // 顶点表，MAXV为已定义常量
    int Edge[MAXV][MAXV];       // 邻接矩阵
} MGraph;

int printVertices(MGraph G)
{
    int cntK = 0;
    for (int i = 0; i < G.numVertices; i++) {
        int inDegree = 0, outDegree = 0;          // 统计每个结点的入度和出度
        for (int j = 0; j < G.numVertices; j++) {
            if (G.Edge[i][j] != 0)      // 每行不为 0 的元素使出度加 1
                outDegree++;
            if (G.Edge[j][i] != 0)      // 每列不为 0 的元素使出度加 1
                inDegree++;
        }
        if (outDegree > inDegree) {
            cntK++;                                  // 统计 K 顶点
            printf("%c ", G.VerticesList[i]);  // 打印 K 顶点
        }
    }

    return cntK;            // 返回 K 顶点数量
}

int main()
{
    MGraph G = {
        4, 3, {'a', 'b', 'c', 'd'},
        {{0, 1, 0, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}}
    };
    printf("%d\n", printVertices(G));
    return 0;
}

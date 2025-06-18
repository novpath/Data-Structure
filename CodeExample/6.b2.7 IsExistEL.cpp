#include <cstdio>

#define NULL nullptr
#define MAXV 100

typedef struct {                // 图的定义
    int numVertices, numEdges;  // 图中实际的顶点数和边数
    char VerticesList[MAXV];    // 顶点表。MAXV 为已定义常量
    int Edge[MAXV][MAXV];       // 邻接矩阵
} MGraph;

int IsExistEL(MGraph G)
{
    int OddDegreeNodes = 0;
    for (int i = 0; i < G.numVertices; ++i) {
        int degree = 0;
        for (int j = 0; j < G.numVertices; ++j) {
            if (G.Edge[i][j] != 0) {
                ++degree;
            }
        }
        if (degree % 2 == 1)
            OddDegreeNodes++;
    }
    if (OddDegreeNodes == 0 || OddDegreeNodes == 2)
        return 1;
    return 0;
}

int main()
{
    MGraph G = {
        4, 3, {'a', 'b', 'c', 'd'},
        {{0, 1, 0, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 0, 1, 0}}
    };
    if (IsExistEL(G))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

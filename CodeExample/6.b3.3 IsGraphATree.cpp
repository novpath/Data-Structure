#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MaxSize 100

typedef struct {                // 图的定义
    int numVertices, numEdges;  // 图中实际的顶点数和边数
    char VerticesList[MaxSize]; // 顶点表
    int Edge[MaxSize][MaxSize]; // 邻接矩阵
} MGraph;

void DFS(const MGraph &G, int i, int &edgeNum, int &vexNum, int visit[])
{
    visit[i] = true;
    vexNum++;
    for (int j = 0; j < G.numVertices; j++) {
        if (G.Edge[i][j] != 0) {
            edgeNum++;
            if (!visit[j]) {
                DFS(G, j, edgeNum, vexNum, visit);
            }
        }
    }
}

bool IsGraphATree(const MGraph &G)
{
    int edgeNum = 0, vexNum = 0;
    int *visit = (int *) malloc(sizeof(int) * G.numVertices);
    for (int i = 0; i < G.numVertices; i++)
        visit[i] = false;
    if (visit == NULL) return false;
    DFS(G, 0, edgeNum, vexNum, visit);

    free(visit);
    return (edgeNum == 2 * (G.numVertices - 1)) && (vexNum == G.numVertices);
}

void PrintResult(int flag)
{
    if (flag)
        printf("Yes\n");
    else
        printf("No\n");
}

int main()
{
    MGraph G = {
        4, 0, {'a', 'b', 'c', 'd'},
        {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
    };
    MGraph G1 = {
        4, 3, {'a', 'b', 'c', 'd'},
        {{0, 1, 0, 0}, {1, 0, 1, 1}, {0, 1, 0, 0}, {0, 1, 0, 0}}
    };
    MGraph G2 = {
        4, 4, {'a', 'b', 'c', 'd'},
        {{0, 1, 0, 0}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 1, 1, 0}}
    };
    PrintResult(IsGraphATree(G));
    PrintResult(IsGraphATree(G1));
    PrintResult(IsGraphATree(G2));

    return 0;
}

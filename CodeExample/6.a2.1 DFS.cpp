#include <cstdio>

#define MaxVertexNum 10  /* 最大顶点数设为10 */
#define INFINITY 65535   /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */

typedef struct GNode *PtrToGNode;

struct GNode {
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
};

typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */
bool Visited[MaxVertexNum]; /* 顶点的访问标记 */

MGraph CreateGraph(); /* 创建图并且将Visited初始化为false；裁判实现，细节不表 */

void Visit(Vertex V)
{
    printf(" %d", V);
}

void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex))
{
    Visit(V);
    Visited[V] = true;
    for (int w = 0; w < Graph->Nv; w++) {
        if (Visited[w] == false && Graph->G[V][w] == 1) {
            DFS(Graph, w, Visit);
        }
    }
}

int main()
{
    Vertex V;

    MGraph G = CreateGraph();
    scanf("%d", &V);
    printf("DFS from %d:", V);
    DFS(G, V, Visit);

    return 0;
}

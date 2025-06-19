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

void AddEdge(ALGraph &G, int v, int w);
void InitGraph(ALGraph &G);
ALGraph CreateGraph1();
ALGraph CreateGraph2();
void PrintGraph(const ALGraph &G);

bool IsBipartite(const ALGraph &G)
{
    int *color = (int *) malloc(sizeof(int) * G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
        color[i] = 0;

    int *q = (int *) malloc(sizeof(int) * G.vexnum);
    for (int i = 0; i < G.vexnum; ++i) {
        if (color[i] == 0) {
            int front = 0, rear = 0;
            q[rear++] = i;
            color[i] = 1;
            while (front != rear) {
                int node = q[front++];
                int cNei = (color[node] == 1 ? 2 : 1);
                for (ArcNode *p = G.vertices[node].firstarc; p; p = p->nextarc) {
                    int neighbor = p->adjvex;
                    if (color[neighbor] == 0) {
                        q[rear++] = neighbor;
                        color[neighbor] = cNei;
                    } else if (color[neighbor] != cNei) {
                        free(color);
                        free(q);
                        return false;
                    }
                }
            }
        }
    }
    free(color);
    free(q);
    return true;
}

int main()
{
    // 创建并打印第一个图
    ALGraph G1 = CreateGraph1();
    printf("G1's Adjacency List:\n");
    PrintGraph(G1);
    printf("\n");

    // 创建并打印第二个图
    ALGraph G2 = CreateGraph2();
    printf("G2's Adjacency List:\n");
    PrintGraph(G2);

    printf("G1 %s Bipartite Graph.\n", IsBipartite(G1) ? "is" : "is no");
    printf("G2 %s Bipartite Graph.\n", IsBipartite(G2) ? "is" : "is no");

    return 0;
}

// 添加无向边（双向）
void AddEdge(ALGraph &G, int v, int w)
{
    // 添加 v->w 的边
    ArcNode *arc_vw = new ArcNode;
    arc_vw->adjvex = w;
    arc_vw->nextarc = G.vertices[v].firstarc;
    G.vertices[v].firstarc = arc_vw;

    // 添加 w->v 的边
    ArcNode *arc_wv = new ArcNode;
    arc_wv->adjvex = v;
    arc_wv->nextarc = G.vertices[w].firstarc;
    G.vertices[w].firstarc = arc_wv;
}

// 初始化图结构
void InitGraph(ALGraph &G)
{
    G.vexnum = 7; // 7个顶点 a-g
    G.arcnum = 0; // 边数初始为0，后续添加边时递增

    // 初始化顶点数据
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = static_cast<char>('a' + i); // 顶点字符：a, b, c, d, e, f, g
        G.vertices[i].firstarc = NULL;
    }
}

// 创建第一个图：边为 ab, ac, bd, cd, ce, ef, df, dg
ALGraph CreateGraph1()
{
    ALGraph G;
    InitGraph(G);

    // 添加边（顶点索引：a=0, b=1, c=2, d=3, e=4, f=5, g=6）
    AddEdge(G, 0, 1); // ab
    AddEdge(G, 0, 2); // ac
    AddEdge(G, 1, 3); // bd
    AddEdge(G, 2, 3); // cd
    AddEdge(G, 2, 4); // ce
    AddEdge(G, 4, 5); // ef
    AddEdge(G, 3, 5); // df
    AddEdge(G, 3, 6); // dg

    G.arcnum = 8; // 共8条边
    return G;
}

// 创建第二个图：边为 ab, ac, bd, ce, ed, cf, dg, eg
ALGraph CreateGraph2()
{
    ALGraph G;
    InitGraph(G);

    // 添加边（顶点索引：a=0, b=1, c=2, d=3, e=4, f=5, g=6）
    AddEdge(G, 0, 1); // ab
    AddEdge(G, 0, 2); // ac
    AddEdge(G, 1, 3); // bd
    AddEdge(G, 2, 4); // ce
    AddEdge(G, 4, 3); // ed (de)
    AddEdge(G, 2, 5); // cf
    AddEdge(G, 3, 6); // dg
    AddEdge(G, 4, 6); // eg

    G.arcnum = 8; // 共8条边
    return G;
}

// 打印邻接表（可选，用于验证）
void PrintGraph(const ALGraph &G)
{
    printf("VexNum: %d, EdgeNum: %d\n", G.vexnum, G.arcnum);
    for (int i = 0; i < G.vexnum; i++) {
        printf("Vex %c: ", G.vertices[i].data);
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            printf("-> %c", 'a' + p->adjvex);
            p = p->nextarc;
        }
        printf(" -> NULL\n");
    }
}

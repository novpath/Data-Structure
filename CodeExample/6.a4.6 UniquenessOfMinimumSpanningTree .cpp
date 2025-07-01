#include <stdio.h>
#include <stdlib.h>

#define MaxEdgeNum 130000       // 500 个顶点边总数的一个上界
#define MaxVertexNum 501

typedef struct {
    int u, v;       // 边的两个顶点
    int weight;     // 边的权重
} Edge;

typedef int SetType[MaxVertexNum];
SetType S;

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
    if (S[root2] < S[root1]) {
        S[root2] += S[root1];
        S[root1] = root2;
    } else {
        S[root1] += S[root2];
        S[root2] = root1;
    }
}

int edge_cmp(const void *a, const void *b)
{
    Edge *edgeA = (Edge *) a;
    Edge *edgeB = (Edge *) b;
    return edgeA->weight - edgeB->weight;
}

int main()
{
    int n, m;  // 顶点数和边数
    scanf("%d %d", &n, &m);
    Edge edges[MaxEdgeNum];  // 存储所有边
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
        edges[i].u--;   // 转换为0-based索引
        edges[i].v--;
    }
    // 按权重排序边
    qsort(edges, m, sizeof(Edge), edge_cmp);
    // 第一遍Kruskal：构建最小生成树
    InitializeSet(n);
    int totalWeight = 0;             // 最小生成树总权重
    int connectedComponents = n;     // 初始连通分量数
    int criticalEdges[MaxVertexNum]; // 存储关键边索引
    int criticalCount = 0;           // 关键边数量
    int hasDuplicateWeights = 0;     // 是否有重复权重标志
    for (int i = 0; i < m; i++) {
        int rootU = Find(edges[i].u);
        int rootV = Find(edges[i].v);
        if (rootU != rootV) {
            Union(rootU, rootV);
            totalWeight += edges[i].weight;
            connectedComponents--;
            // 检查相邻边是否有相同权重
            int isDuplicate = 0;
            if (i > 0 && edges[i].weight == edges[i - 1].weight) isDuplicate = 1;
            if (i < m - 1 && edges[i].weight == edges[i + 1].weight) isDuplicate = 1;
            if (isDuplicate) {
                criticalEdges[criticalCount++] = i;
                hasDuplicateWeights = 1;
            }
        }
    }
    // 检查图是否连通
    if (connectedComponents > 1) {
        // 统计连通分量个数
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (S[i] < 0) components++;
        }
        printf("No MST\n%d\n", components);
        return 0;
    }
    // 检查最小生成树是否唯一
    int isUnique = 1;
    if (hasDuplicateWeights) {
        for (int idx = 0; idx < criticalCount; idx++) {
            int skipIndex = criticalEdges[idx];
            InitializeSet(n);
            int tempWeight = 0;
            int edgesUsed = 0;
            // 构建跳过当前关键边的生成树
            for (int i = 0; i < m; i++) {
                if (i == skipIndex) continue; // 跳过关键边
                int rootU = Find(edges[i].u);
                int rootV = Find(edges[i].v);
                if (rootU != rootV) {
                    Union(rootU, rootV);
                    tempWeight += edges[i].weight;
                    edgesUsed++;
                }
            }
            // 如果找到权重相同的生成树，说明不唯一
            if (edgesUsed == n - 1 && tempWeight == totalWeight) {
                isUnique = 0;
                break;
            }
        }
    }
    // 输出结果
    printf("%d\n", totalWeight);
    printf("%s\n", isUnique ? "Yes" : "No");

    return 0;
}

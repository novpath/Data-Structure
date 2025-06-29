#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NULL nullptr
#define MaxVertexNum 200

typedef struct MGNode {
    int vexnum, arcnum;
    int edge[MaxVertexNum][MaxVertexNum];
} MGNode, *MGraph;

MGraph BuildGraph()
{
    MGraph G = (MGraph) malloc(sizeof(MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G->edge[i][j] = 0;
        }
    }
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        G->edge[v][w] = 1;
        G->edge[w][v] = 1;
    }
    return G;
}

void Check(MGraph G)
{
    int k;
    scanf("%d", &k);
    while (k--) {
        int n;
        scanf("%d", &n);
        bool flag = true;
        int a[n];
        bool visited[n];
        memset(visited, false, sizeof(visited));
        for (int i = 0; i < n; i++) {
            if (n != G->vexnum + 1)
                flag = false;
            scanf("%d", &a[i]);
            if (visited[a[i]] == true && i != n - 1)
                flag = false;
            if (!visited[a[i]])
                visited[a[i]] = true;
            if (i >= 1 && G->edge[a[i - 1]][a[i]] == 0)
                flag = false;
        }
        if (a[0] != a[n - 1])
            flag = false;
        if (flag)
            printf("YES");
        else
            printf("NO");
        if (k != 0)
            printf("\n");
    }
}

int main()
{
    MGraph G = BuildGraph();
    Check(G);
    free(G);
    return 0;
}

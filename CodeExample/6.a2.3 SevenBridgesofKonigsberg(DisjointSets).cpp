#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MaxVertexNum 1000
typedef int VertexType;
typedef int EdgeType;

typedef struct MGNode {
    int vexnum, arcnum;
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int degree[MaxVertexNum];
} MGNode, *MGraph;

int S[MaxVertexNum];

MGraph CreateGraph();
MGraph BuildGraph();
bool CheckG(MGraph G);
void Union(int S[], int Root1, int Root2);
int Find(int S[], int x);

int main()
{
    memset(S, -1, sizeof(int) * MaxVertexNum);
    MGraph G = BuildGraph();
    int connected = 0;
    for (int i = 0; i < G->vexnum; i++) {
        if (S[i] <= -1)
            connected++;
    }
    if (connected >= 2)
        printf("0\n");
    else
        printf("%d\n", CheckG(G));

    free(G);
    return 0;
}

MGraph CreateGraph()
{
    MGraph G = (MGraph) malloc(sizeof(struct MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (int v = 0; v < G->vexnum; v++) {
        G->degree[v] = 0;
    }

    return G;
}

MGraph BuildGraph()
{
    MGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        G->edge[v - 1][w - 1] = 1;
        G->edge[w - 1][v - 1] = 1;
        G->degree[v - 1]++;
        G->degree[w - 1]++;
        Union(S, Find(S, v - 1), Find(S, w - 1));
    }
    return G;
}

bool CheckG(MGraph G)
{
    for (int v = 0; v < G->vexnum; v++)
        if (G->degree[v] % 2 == 1)
            return false;
    return true;
}

void Union(int S[], int Root1, int Root2)
{
    if (Root1 == Root2) return;
    if (S[Root2] > S[Root1]) {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    } else {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

int Find(int S[], int x)
{
    int root = x;
    while (S[root] >= 0)
        root = S[root];
    while (x != root) {
        int t = S[x];
        S[x] = root;
        x = t;
    }
    return root;
}

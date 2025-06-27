#include <cstdio>
#include <cstdlib>

#define NULL nullptr

#define MaxVertexNum 100
#define INFINITY 65535
typedef int VertexType;
typedef int WeightType;

typedef struct MGNode {
    int vexnum, arcnum;
    WeightType edge[MaxVertexNum][MaxVertexNum];
} MGNode, *MGraph;

MGraph CreateGraph();
MGraph BuildGraph();
void Floyd(MGraph G, WeightType D[][MaxVertexNum]);

WeightType FindMaxDist(WeightType D[][MaxVertexNum], VertexType i, int N);
void FindAnimal(MGraph G);

int main()
{
    MGraph G = BuildGraph();
    FindAnimal(G);

    free(G);
    return 0;
}

MGraph CreateGraph()
{
    MGraph G = (MGraph) malloc(sizeof(struct MGNode));
    scanf("%d %d", &G->vexnum, &G->arcnum);
    for (VertexType v = 0; v < G->vexnum; v++) {
        for (VertexType w = 0; w < G->vexnum; w++) {
            G->edge[v][w] = INFINITY;
        }
    }
    return G;
}

MGraph BuildGraph()
{
    MGraph G = CreateGraph();
    for (int i = 0; i < G->arcnum; i++) {
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        v--, w--;
        G->edge[v][w] = weight;
        G->edge[w][v] = weight;
    }
    return G;
}

void Floyd(MGraph G, WeightType D[][MaxVertexNum])
{
    int i, j;
    for (i = 0; i < G->vexnum; i++) {
        for (j = 0; j < G->vexnum; j++) {
            D[i][j] = G->edge[i][j];
        }
    }
    for (int k = 0; k < G->vexnum; k++) {
        for (i = 0; i < G->vexnum; i++) {
            for (j = 0; j < G->vexnum; j++) {
                if (D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
            }
        }
    }
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum], VertexType i, int N)
{
    WeightType MaxDist = 0;
    for (VertexType j = 0; j < N; j++) {
        if (i != j && D[i][j] > MaxDist)  /* i == j 时，距离为无穷大 */
            MaxDist = D[i][j];
    }
    return MaxDist;
}

void FindAnimal(MGraph G)
{
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist = 0, MiniDist = INFINITY;
    Floyd(G, D);
    VertexType animal;
    for (int i = 0; i < G->vexnum; i++) {
        MaxDist = FindMaxDist(D, i, G->vexnum);
        if (MaxDist == INFINITY) {
            printf("0\n");
            return;
        }
        if (MiniDist > MaxDist) {
            MiniDist = MaxDist;
            animal = i + 1;
        }
    }
    printf("%d %d\n", animal, MiniDist);
}
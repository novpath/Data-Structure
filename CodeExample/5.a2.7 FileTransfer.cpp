#include <cstdio>

#define MaxSize 10000
typedef int ElementType;
typedef int SetName;

/*-----  集合定义 -----*/
typedef ElementType SetType[MaxSize];
void Initialization(SetType S, int n);
void Union(SetType S, SetName Root1, SetName Root2);
SetName Find(SetType S, ElementType X);
/*-----  集合定义结束 -----*/

void InputConnection(SetType S);
void CheckConnection(SetType S);
void CheckNetwork(const SetType S, int n);

int main()
{
    SetType S;
    int n;
    char in;
    scanf("%d", &n);
    Initialization(S, n);
    do {
        scanf(" %c", &in);
        switch (in) {
            case 'I': InputConnection(S);
                break;
            case 'C': CheckConnection(S);
                break;
            default: CheckNetwork(S, n);
        }
    } while (in != 'S');
    return 0;
}

void Initialization(SetType S, int n)
{
    for (int i = 0; i < n; i++)
        S[i] = -1;
}

void Union(SetType S, ElementType Root1, ElementType Root2)
{
    if (Root1 == Root2) return;
    if (S[Root2] > S[Root1]) {             // Root2结点数更少
        S[Root1] += S[Root2];              // 累加集合树的结点总数
        S[Root2] = Root1;                  // 小树合并到大树
    } else {                               // Root1结点数更少
        S[Root2] += S[Root1];              // 累加结点总数
        S[Root1] = Root2;                  // 小树合并到大树
    }
}

int Find(SetType S, ElementType x)
{
    ElementType root = x;
    while (S[root] >= 0)    // 循环找到根
        root = S[root];
    while (x != root) {     // 压缩路径
        int t = S[x];       // t 指向 x 的父节点
        S[x] = root;        // x 直接挂到根结点下面
        x = t;
    }
    return root;            // 返回根结点编号
}

void InputConnection(SetType S)
{
    ElementType u, v;
    scanf("%d %d\n", &u, &v);
    SetName Root1 = Find(S, u - 1);
    SetName Root2 = Find(S, v - 1);
    if (Root1 != Root2)
        Union(S, Root1, Root2);
}

void CheckConnection(SetType S)
{
    ElementType u, v;

    scanf("%d %d\n", &u, &v);
    SetName Root1 = Find(S, u - 1);
    SetName Root2 = Find(S, v - 1);
    if (Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
}

void CheckNetwork(const SetType S, int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] < 0)
            cnt++;
    }
    if (cnt == 1)
        printf("The network is connected.");
    else
        printf("There are %d components.", cnt);
}

#include <cstdio>
#include <cstring>
#include <malloc.h>

#define MINH (-10001)
#define NULL nullptr
#define MaxCodeLen 64

typedef struct HuffmanNode {
    int weight;
    char ch;
    struct HuffmanNode *left, *right;
} HNode, *HuffmanTree;

HuffmanTree H;
int size, n;
int weightArr[MaxCodeLen];

int WPL(HuffmanTree T, int Depth)
{
    if (!T->left && !T->right)
        return (Depth * T->weight);
    return WPL(T->left, Depth + 1) + WPL(T->right, Depth + 1);
}

void Insert(HuffmanTree x, HuffmanTree H[])
{
    if (size == n)
        return;
    int i;
    for (i = ++size; H[i / 2]->weight > x->weight; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

HuffmanTree Delete(HuffmanTree H[])
{
    if (size == 0)
        return NULL;

    HuffmanTree minItem = H[1];
    HuffmanTree lastItem = H[size--];
    int parent, child;
    for (parent = 1; parent * 2 <= size; parent = child) {
        child = parent * 2;

        if (child != size && H[child + 1]->weight < H[child]->weight) {
            child++;
        }

        if (lastItem->weight <= H[child]->weight) break;
        H[parent] = H[child];
    }
    H[parent] = lastItem;

    return minItem;
}

HuffmanTree *CreateMinHeap()
{
    scanf("%d", &n);
    size = 0;
    HuffmanTree *H = (HuffmanTree *) malloc(sizeof(HuffmanTree) * (n + 1));
    H[0] = (HuffmanTree) malloc(sizeof(HNode));
    H[0]->weight = MINH;
    H[0]->left = H[0]->right = NULL;
    for (int i = 1; i <= n; i++) {
        char ch;
        int weight;
        scanf(" %c %d", &ch, &weight);
        weightArr[i] = weight;
        HuffmanTree node = (HuffmanTree) malloc(sizeof(HNode));
        node->ch = ch;
        node->weight = weight;
        node->left = node->right = NULL;
        Insert(node, H);
    }

    return H;
}

HuffmanTree BuildHuffmanTree(HuffmanTree H[])
{
    int mergeNum = size;
    for (int i = 1; i < mergeNum; i++) {
        HuffmanTree T = (HuffmanNode *) malloc(sizeof(HNode));
        T->left = Delete(H);
        T->right = Delete(H);
        T->weight = T->left->weight + T->right->weight;
        Insert(T, H);
    }
    return Delete(H);
}

void DeleteSubtree(HuffmanTree &T)
{
    if (T) {
        DeleteSubtree(T->left);
        DeleteSubtree(T->right);
        free(T);
        T = NULL;
    }
}

void Check(int MinWPL, HuffmanTree H[])
{
    int m;
    int IsShortestWPL, IsPreFixCode;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int codeLen = 0;
        IsShortestWPL = 0, IsPreFixCode = 1;
        HuffmanTree p = (HuffmanTree) malloc(sizeof(HNode));
        p->weight = 0;
        p->left = p->right = NULL;
        HuffmanTree root = p;
        for (int j = 1; j <= n; j++) {
            p = root;
            char code[n + 1];
            char ch;
            scanf(" %c%s", &ch, code);
            codeLen += weightArr[j] * (int) strlen(code);
            int k = 0;
            while (code[k] != '\0') {
                int CreateNodeFlag = 0;
                if (p->weight != 0) {
                    IsPreFixCode = 0;
                    break;
                }
                if (code[k] == '0') {
                    if (p->left == NULL) {
                        p->left = (HuffmanTree) malloc(sizeof(HNode));
                        p->left->left = p->left->right = NULL;
                        p->left->weight = 0;
                        CreateNodeFlag = 1;
                    }
                    p = p->left;
                } else {
                    if (p->right == NULL) {
                        p->right = (HuffmanTree) malloc(sizeof(HNode));
                        p->right->left = p->right->right = NULL;
                        p->right->weight = 0;
                        CreateNodeFlag = 1;
                    }
                    p = p->right;
                }
                if (code[k + 1] == '\0')
                    p->weight = weightArr[j];
                if (!CreateNodeFlag && code[k + 1] == '\0') {
                    IsPreFixCode = 0;
                    break;
                }
                k++;
            }
        }
        if (codeLen == MinWPL)
            IsShortestWPL = 1;
        if (IsShortestWPL && IsPreFixCode)
            printf("Yes\n");
        else
            printf("No\n");
        DeleteSubtree(root);
    }
}

int main()
{
    HuffmanTree *H = CreateMinHeap();
    HuffmanTree T = BuildHuffmanTree(H);
    Check(WPL(T, 0), H);
    DeleteSubtree(T);
    return 0;
}

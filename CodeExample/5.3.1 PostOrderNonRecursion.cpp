#include <cstdio>
#include <cstdlib>
#define NULL nullptr
#define MaxSize 100

typedef struct BiTNode {
    int data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct SqStack {
    BiTree data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S)
{
    S.top = -1;
}

bool Push(SqStack &S, BiTree x)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, BiTree &x)
{
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

// 获取栈顶元素
BiTree GetTop(const SqStack &S)
{
    return S.top == -1 ? NULL : S.data[S.top];
}

void visit(BiTree T)
{
    printf("%d ", T->data);
}

void PostorderNonRecursion(BiTree T)
{
    SqStack S;
    InitStack(S);
    BiTree p = T, lastVisited = NULL;
    while (p || S.top != -1) {
        if (p) {
            Push(S, p);
            p = p->lchild;               // 走到最左边
        } else {
            BiTree topNode = GetTop(S);
            if (topNode->rchild && topNode->rchild != lastVisited) {
                p = topNode->rchild;     // 转向右子树
            } else {                     // 右孩子为空或者右孩子访问完了可以访问结点
                Pop(S, topNode); // 访问节点
                visit(topNode);
                lastVisited = topNode;
                p = NULL;                // 处理完结点强制置空，通过栈返回上层避免结点重新入栈死循环
            }
        }
    }
}

// 创建新节点
BiTree CreateNode(int value)
{
    auto newNode = static_cast<BiTree>(malloc(sizeof(BiTNode)));
    newNode->data = value;
    newNode->lchild = newNode->rchild = NULL;
    return newNode;
}

int main()
{
    /* 构建测试树：
          1
        /   \
       2     3
      / \   /
     4   5 6
    */
    BiTree root = CreateNode(1);
    root->lchild = CreateNode(2);
    root->rchild = CreateNode(3);
    root->lchild->lchild = CreateNode(4);
    root->lchild->rchild = CreateNode(5);
    root->rchild->lchild = CreateNode(6);

    printf("PostOrder Sequence: ");
    PostorderNonRecursion(root);  // 正确输出：4 5 2 6 3 1

    return 0;
}

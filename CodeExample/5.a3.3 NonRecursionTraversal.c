#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;
};

/*------堆栈的定义-------*/
typedef Position SElementType;
typedef struct SNode *PtrToSNode;

struct SNode {
    SElementType Data;
    PtrToSNode Next;
};

typedef PtrToSNode Stack;

/* 裁判实现，细节不表 */
Stack CreateStack();
bool IsEmpty(Stack S);
bool Push(Stack S, SElementType X);
SElementType Pop(Stack S); /* 删除并仅返回S的栈顶元素 */
SElementType Peek(Stack S);/* 仅返回S的栈顶元素 */
/*----堆栈的定义结束-----*/

BinTree CreateBinTree(); /* 裁判实现，细节不表 */
void InorderTraversal(BinTree BT);
void PreorderTraversal(BinTree BT);
void PostorderTraversal(BinTree BT);

int main()
{
    BinTree BT = CreateBinTree();
    printf("Inorder:");
    InorderTraversal(BT);
    printf("\n");
    printf("Preorder:");
    PreorderTraversal(BT);
    printf("\n");
    printf("Postorder:");
    PostorderTraversal(BT);
    printf("\n");
    return 0;
}

/* 你的代码将被嵌在这里 */
void PreorderTraversal(BinTree T)
{
    BinTree p = T;
    Stack S = CreateStack();
    while (p || !IsEmpty(S)) {
        if (p) {
            printf(" %c", p->Data);
            Push(S, p);
            p = p->Left;
        } else {
            p = Pop(S);
            p = p->Right;
        }
    }
}

void InorderTraversal(BinTree T)
{
    BinTree p = T;
    Stack S = CreateStack();
    while (p || !IsEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->Left;
        } else {
            p = Pop(S);
            printf(" %c", p->Data);
            p = p->Right;
        }
    }
}

void PostorderTraversal(BinTree T)
{
    Stack S = CreateStack();
    BinTree p = T;
    while (p || !IsEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->Left;               // 走到最左边
        } else {
            p = Peek(S);
            if (p->flag != 1) {
                p->flag = 1;
                p = p->Right;          // 转向右子树
            } else {                   // 右孩子为空或者右孩子访问完了可以访问结点
                printf(" %c", p->Data);
                p = Pop(S);            // 访问节点
                p = NULL;              // 处理完结点强制置空，通过栈返回上层避免结点重新入栈死循环
            }
        }
    }
}

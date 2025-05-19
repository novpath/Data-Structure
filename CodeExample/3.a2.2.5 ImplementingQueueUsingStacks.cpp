#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct {
    int *data;      // 数组指针
    int top;        // 栈顶指针
    int MaxSize;    // 栈空间大小
} *Stack;

Stack InitStack(int n)
{
    Stack s = (Stack)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->MaxSize = n;
    return s;
}

int IsEmpty (Stack S)
{
    if (S == NULL)
        return -1;
    return (S->top == -1 ? 1 : 0);
}

int IsFull(Stack S)
{
    if (S == NULL)
        return -1;
    return (S->top == S->MaxSize - 1 ? 1 : 0);
}

void Push(Stack S, ElementType item)
{
    if (S == NULL)
        return ;
    S->data[++S->top] = item;          // 指针先加 1，再入栈
}

ElementType Pop(Stack S)
{
    if (S == NULL)
        return -1;
    return S->data[S->top--];
}

void AddQ(Stack S1, Stack S2, ElementType item)
{
    if (!IsFull(S1)) {
        Push(S1, item);
    } else if (IsEmpty(S2)) {
        while (!IsEmpty(S1))
            Push(S2, Pop(S1));
        Push(S1, item);
    } else {
        printf("ERROR:Full\n");
    }
}

ElementType DeleteQ(Stack &S1, Stack &S2)
{
    ElementType temp;
    if (!IsEmpty(S2)) {
        temp = Pop(S2);
        printf("%d\n", temp);
        return temp;
    } else if (!IsEmpty(S1)) {
        while (!IsEmpty(S1))
            Push(S2, Pop(S1));
        temp = Pop(S2);
        printf("%d\n", temp);
        return temp;
    } else {
        printf("ERROR:Empty\n");
        return -1;
    }
}

int main()
{
    int N1, N2;
    int x;
    scanf("%d %d", &N1, &N2);
    Stack S1 = InitStack(N1);
    Stack S2 = InitStack(N2);
    if (N1 > N2) {
        Stack tmp = S1;
        S1 = S2;
        S2 = tmp;
    }
    char ch;
    while (scanf(" %c", &ch) == 1 && ch != 'T') {
        switch (ch) {
            case 'A': {
                scanf(" %d", &x);
                AddQ(S1, S2, x);
                break;
            }
            case 'D': {
                DeleteQ(S1, S2);
                break;
            }
            default: break;
        }
    }
    free(S1);
    free(S2);
    return 0;
}
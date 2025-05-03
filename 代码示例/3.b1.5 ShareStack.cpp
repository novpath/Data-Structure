#include <stdio.h>
#define MaxSize 100            // 存储数据元素的最大个数

typedef int ElementType;

typedef struct ShareStack {
    ElementType data[MaxSize]; 
    int Top0;                  // 堆栈 0 的栈顶指针
    int Top1;                  // 堆栈 1 的栈顶指针
} ShStack, *LinkShStack;

void InitStack(ShStack &S)  // 初始化栈顶指针
{
    S.Top0 = -1;
    S.Top1 = MaxSize;
}

bool Push(ShStack *PtrS, ElementType x, int Tag)// Tag 作为区分两个堆栈的标志，取值为 0 和 1
{          
    if (Tag != 0 && Tag != 1)
        return false;                             
    if (PtrS->Top1 - PtrS->Top0 == 1) {         // 两个栈顶指针相邻，堆栈满
        return false;
    }
    if (Tag == 0)                               // 对第 0 个堆栈操作
        PtrS->data[++(PtrS->Top0)] = x;
    else                                        // 对第 1 个堆栈操作
        PtrS->data[--(PtrS->Top1)] = x;
    return true;
}

bool Pop(ShStack *PtrS, ElementType &x, int Tag) // Tag 作为区分两个堆栈的标志，取值为 0 和 1
{
    if (Tag != 0 && Tag != 1)
        return false;                         
    if (Tag == 0) {                   // 对第 0 个堆栈操作
        if (PtrS->Top0 == -1) {       // 栈 0 空
            return false;
        } else {
            x = PtrS->data[(PtrS->Top0)--];
            return true;
        }
    } else {                          // 对第 1 个堆栈操作
        if (PtrS->Top1 == MaxSize) {  // 栈 1 空
            return false;
        } else {
            x = PtrS->data[(PtrS->Top1)++];
            return true;
        }
    }
}

int main()
{
	ShStack s;
	InitStack(s);
	for (int i = 0; i < 100; i++) {
		s.data[i] = 0;
	}
	for (int i = 0; i < 100; i++) {
		printf("%3d ", s.data[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
	for (int i = 0, j = 99; i < 50; i++, j--) {
		Push(&s, i + 1, 0);
		Push(&s, j + 1, 1);
	}
	for (int i = 0; i < 100; i++) {
		printf("%3d ", s.data[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	int a, b;
	Pop(&s, a, 0);
	Pop(&s, b, 1);
	printf("a = %3d, b = %3d", a, b);

    return 0;
}


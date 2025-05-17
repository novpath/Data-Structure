#include <stdio.h>

typedef struct {
    int n;       // 待处理盘子数量
    char a;      // 起始柱
    char c;      // 目标柱
    char b;      // 辅助柱
} Frame;

void hanio(int n, char a, char c, char b) {
    Frame stack[100];                // 申请 100 层栈空间
    int top = -1;
    stack[++top] = {n, a, c, b};  // 初始化栈
    while (top >= 0) {
        Frame elem = stack[top--];   // 取出栈元素，模拟函数调用
        if (elem.n == 1) {
            printf("%c -> %c\n", elem.a, elem.c);
        } else {
            // 先模拟递归的后半部分（因为栈是后进先出，最后入栈的最先出栈）
            stack[++top] = {elem.n - 1, elem.b, elem.c, elem.a};
            // 中间的单步移动
            stack[++top] = {1, elem.a, elem.c, elem.b};
            // 再模拟递归的前半部分
            stack[++top] = {elem.n - 1, elem.a, elem.b, elem.c};
        }
    }
}

int main() {                 // 示例 main 函数
    int n;
    scanf("%d", &n);
    hanio(n, 'a', 'c', 'b');
    return 0;
}
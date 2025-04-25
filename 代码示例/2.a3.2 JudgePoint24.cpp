#include <stdio.h>
#include <stdlib.h> 

#define EPS 1e-6
#define INF 1e10

char op[4] = {'+', '-', '*', '/'};

double cal(double x, double y, char op)
{
	switch (op) {
		case '+': return x + y;
		case '-': return x - y;
		case '*': return x * y;
		case '/': 
		    if (y > -EPS && y < EPS)
		    	return INF;
		    return x / y;
		default: return 0;
	}
}

double mode(double a, double b, double c, double d, char op1, char op2, char op3, int m)
{
	switch (m) {
		case 1: return cal(cal(cal(a, b, op1), c, op2), d, op3);
		case 2: return cal(cal(a, b, op1), cal(c, d, op3), op2);
		case 3: return cal(cal(a, cal(b, c, op2), op1), d, op3);
		case 4: return cal(a, cal(cal(b, c, op2), d, op3), op1);
		case 5: return cal(a, cal(b, cal(c, d, op3), op2), op1);
	}
    return 0;
}

int print(int a, int b, int c, int d)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                char op1 = op[i], op2 = op[j], op3 = op[k];
                for (int m = 1; m <= 5; m++) {
                    double result = mode(a, b, c, d, op1, op2, op3, m);
                    if ((result - 24 < EPS && result - 24 > -EPS)) {
                        switch (m) {
                            case 1: printf("((%d%c%d)%c%d)%c%d\n", a, op1, b, op2, c, op3, d); return 1;
                            case 2: printf("(%d%c%d)%c(%d%c%d)\n", a, op1, b, op2, c, op3, d); return 1;
                            case 3: printf("(%d%c(%d%c%d))%c%d\n", a, op1, b, op2, c, op3, d); return 1;
                            case 4: printf("%d%c((%d%c%d)%c%d)\n", a, op1, b, op2, c, op3, d); return 1;
                            case 5: printf("%d%c(%d%c(%d%c%d))\n", a, op1, b, op2, c, op3, d); return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void dfs(int start, int len, int a[]) {
    if (start == len - 1) {               // 完成一个排列
    	if(print(a[0], a[1], a[2], a[3]))
    		exit(0);
        return ;
    }
    
    for (int i = start; i < len; i++) {
        swap(&a[start], &a[i]);           // 交换元素
        dfs(start + 1, len, a);           // 递归下一层
        swap(&a[start], &a[i]);           // 回溯恢复
    }
}

int main() {
    int num[4];
    scanf("%d %d %d %d", &num[0], &num[1], &num[2], &num[3]);
    dfs(0, 4, num);
    printf("-1\n");
    
    return 0;
}

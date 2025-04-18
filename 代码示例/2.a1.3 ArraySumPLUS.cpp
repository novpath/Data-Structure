#include <stdio.h>
#define MAXN 100001                      // 根据题目n的范围调整

int main() {
    int a, n;
    int arr[MAXN] = {0};                 // 初始化数组为0
    int carry = 0;                       // 进位
    scanf("%d %d", &a, &n);
    
    if (n == 0) {
        printf("0");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {        // 计算每一位的和并处理进位
        int total = (n - i) * a + carry;
        arr[i] = total % 10;
        carry = total / 10;
    }
    
    if (carry > 0)                       // 处理最高位的进位
        printf("%d", carry);
    
    for (int i = n - 1; i >= 0; i--)     // 逆序输出数组中的每一位
        printf("%d", arr[i]);
    
    return 0;
}

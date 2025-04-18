#include <stdio.h>

int n;                            // 输入的全排列数字范围（1~n）
int current[10];                  // 保存当前生成的排列序列
int used[10] = {0};               // 标记数字是否已被使用，0 未用 / 1 已用

void print_perm() {               // 打印当前生成的排列
    for (int i = 0; i < n; i++) {
        printf("%d", current[i]); // 逐个打印排列中的数字
    }
    printf("\n");                 // 换行分隔不同排列
}

void generate(int pos) {          // 递归生成全排列的核心函数
    if (pos == n) {               // pos: 当前正在填充的位置（从0开始）
        print_perm();             // 输出当前完整的排列
        return;
    }

    for (int num = 1; num <= n; num++) {  // 按升序遍历所有数字（保证字典序的关键）
        if (!used[num]) {
            used[num] = 1;                // 标记为已使用
            current[pos] = num;           // 将当前数字放入排列的 pos 位置
            generate(pos + 1);            // 递归填充下一位
            used[num] = 0;                // 回溯，完成该分支后取消标记，不需要重置 current[pos]，因为会被后续覆盖
        }
    }
}

int main() {
    scanf("%d", &n);    // 读取输入的n值
    generate(0);        // 从第 0 个位置开始生成排列
    return 0;
}

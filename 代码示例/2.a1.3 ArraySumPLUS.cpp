#include <stdio.h>
#define MAXN 100001                      // ������Ŀn�ķ�Χ����

int main() {
    int a, n;
    int arr[MAXN] = {0};                 // ��ʼ������Ϊ0
    int carry = 0;                       // ��λ
    scanf("%d %d", &a, &n);
    
    if (n == 0) {
        printf("0");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {        // ����ÿһλ�ĺͲ������λ
        int total = (n - i) * a + carry;
        arr[i] = total % 10;
        carry = total / 10;
    }
    
    if (carry > 0)                       // �������λ�Ľ�λ
        printf("%d", carry);
    
    for (int i = n - 1; i >= 0; i--)     // ������������е�ÿһλ
        printf("%d", arr[i]);
    
    return 0;
}

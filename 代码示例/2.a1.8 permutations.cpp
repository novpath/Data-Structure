#include <stdio.h>

int n;                            // �����ȫ�������ַ�Χ��1~n��
int current[10];                  // ���浱ǰ���ɵ���������
int used[10] = {0};               // ��������Ƿ��ѱ�ʹ�ã�0 δ�� / 1 ����

void print_perm() {               // ��ӡ��ǰ���ɵ�����
    for (int i = 0; i < n; i++) {
        printf("%d", current[i]); // �����ӡ�����е�����
    }
    printf("\n");                 // ���зָ���ͬ����
}

void generate(int pos) {          // �ݹ�����ȫ���еĺ��ĺ���
    if (pos == n) {               // pos: ��ǰ��������λ�ã���0��ʼ��
        print_perm();             // �����ǰ����������
        return;
    }

    for (int num = 1; num <= n; num++) {  // ����������������֣���֤�ֵ���Ĺؼ���
        if (!used[num]) {
            used[num] = 1;                // ���Ϊ��ʹ��
            current[pos] = num;           // ����ǰ���ַ������е� pos λ��
            generate(pos + 1);            // �ݹ������һλ
            used[num] = 0;                // ���ݣ���ɸ÷�֧��ȡ����ǣ�����Ҫ���� current[pos]����Ϊ�ᱻ��������
        }
    }
}

int main() {
    scanf("%d", &n);    // ��ȡ�����nֵ
    generate(0);        // �ӵ� 0 ��λ�ÿ�ʼ��������
    return 0;
}

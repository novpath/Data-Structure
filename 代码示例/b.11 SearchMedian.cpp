/* PTA ����ʵ�� 1-3.1 �����������е���λ�� OJ ����֤*/

#include <stdio.h>

int SearchMedian(int A[], int B[], int n)
{
    int i = 0, j = 0;                // ����ָ�� i��j
    while (i < n && j < n) {         // ������������
        if (A[i] < B[j]) {           
            if (i + j == n - 1) {    // �Ѵ��м�λ�ã��� A[i] �� B[j] С
                return A[i];
            }
            i++;
        } else {
            if (i + j == n - 1) {    // �Ѵ��м�λ�ã��� B[j] �� A[i] С
                return b[j];
            }
            j++;
        }
    }
}

int M_Search(int A[], int B[], int n) { // n ��Ϊ���г��� L
    int s1 = 0, e1 = n - 1, mid1, s2 = 0, e2 = n - 1, mid2;
    while (s1 != e1 || s2 != e2) {
        mid1 = (s1 + e1) / 2;
        mid2 = (s2 + e2) / 2;
        if (A[mid1] == B[mid2]) {
            return A[mid1];
        } else if (A[mid1] < B[mid2]) { // �ֱ���������ż������������������Ԫ�ظ������
            if ((s1 + e1) % 2 == 0) {   // ��Ԫ�ظ���Ϊ����
                s1 = mid1;              // ���� A �м����ǰ�Ĳ���
                e2 = mid2;              // ���� B �м���Ժ�Ĳ���
            } else {                    // ��Ԫ�ظ���Ϊż��
                s1 = mid1 + 1;          // ���� A �м�㼰�м����ǰ�Ĳ���
                e2 = mid2;              // ���� B �м���Ժ�Ĳ���
            }
        } else {                      // �ֱ���������ż������������������Ԫ�ظ������
            if ((s1 + e1) % 2 == 0) { // ��Ԫ�ظ���Ϊ����
                e1 = mid1;            // ���� A �м���Ժ�Ĳ���
                s2 = mid2;            // ���� B �м����ǰ�Ĳ���
            } else {                  // ��Ԫ�ظ���Ϊż��
                e1 = mid1;            // ���� A �м���Ժ�Ĳ���
                s2 = mid2 + 1;        // ���� B �м�㼰�м����ǰ�Ĳ���
            }
        }
    }
    return A[s1] < B[s2] ? A[s1] : B[s2];
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int a[n], b[n];
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(i = 0; i < n; i++)
        scanf("%d", &b[i]);
    //printf("%d", SearchMedian(a, b, n));
    printf("%d", M_Search(a, b, n));
    return 0;
}

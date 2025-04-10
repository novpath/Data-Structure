/* ACwing 3874 三元组的最小距离 */

#include <stdio.h>
#define INT_MAX 1e19
typedef long long LL;

LL Abs(LL a)        //计算绝对值
{
    if(a < 0) return -a;
    else return a;
}

bool IsFirstMin(int a, int b, int c)    //是否是三个数中的最小值
{
    if ((a <= b) && (a <= c)) 
        return true;
    return false;
}

LL FindMinTrip(int A[], int l, int B[], int m, int C[], int n)  // D_min 用于记录三元组的最小距离，初始赋值为INT_MAX
{
    int i = 0, j = 0, k = 0;
    LL D_min = INT_MAX, D;
    while (i < l && j < m && k < n && D_min > 0 ) {
        D = Abs(A[i] - B[j]) + Abs(B[j] - C[k]) + Abs(C[k] - A[i]);  // 计算 D
        if (D < D_min) D_min = D;                                    // 更新 D
        if (IsFirstMin(A[i],B[j],C[k])) i++;                         // 更新 a
        else if (IsFirstMin(B[j],C[k],A[i])) j++;
        else k++;
    }
    return D_min;
}

int main()
{
    int l, m, n, i;
    scanf("%d %d %d", &l, &m, &n);
    int a[l], b[m], c[n];
    for (i = 0; i < l; i++)
        scanf("%d", &a[i]); 
    for (i = 0; i < m; i++)
        scanf("%d", &b[i]); 
    for (i = 0; i < n; i++)
        scanf("%d", &c[i]);
    
    printf("%ld", FindMinTrip(a, l, b, m, c, n));
        
    return 0;
}

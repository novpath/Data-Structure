/* SWUST OJ 1036*/

#include <stdio.h>

int ArrMainElement(int A[], int n)
{
    int m = 0, majority = A[0], i;
    for (i = 0; i < n; i++) {
        if (A[i] == majority)
            m++;
        else {
        	m--;
            if (m == 0) {
            	majority = A[i];
            	m++;
			}
		}
    }

    if (m > 0) {
        for (i = m = 0; i < n; i++) {
        	if(A[i] == majority)
        	    m++;
		}
	}
	if(m <= n / 2)
	    majority = -1;
    return majority;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int a[n];
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("%d", ArrMainElement(a, n));
    return 0;
}

#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    scanf("%d", &n);
        
    int a[n];
    double avg = 0, s = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        avg += a[i];
    }
    avg /= n;
    for (int i = 0; i < n; i++) 
        s += (a[i] - avg) * (a[i] - avg);
    
    s = sqrt(s / n);
    printf("%.5f\n", s);
    
    return 0;
}


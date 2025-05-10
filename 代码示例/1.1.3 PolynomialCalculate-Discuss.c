#include <stdio.h>
#include <time.h>
#include <math.h>
clock_t start, stop; 
double duration;
#define MAXN 10   	/* 多项式最大项数，即多项式阶数+1 */
#define MAXK 1e7  	/* 函数运行次数 */
double f1( int n, double a[], double x );
double f2( int n, double a[], double x );
void run(double(*f)(int, double *, double), double a[], int case_n)
{
	int i;
	start = clock();
	for(i = 0; i < MAXK; i ++)
		(*f)(MAXN-1, a, 1.1);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK / MAXK;
	printf("ticks%d = %f\n", case_n, (double)(stop - start));
	printf("duration%d=%6.2e\n", case_n, duration);
}

int main ()
{ 
    int i;
	double a[MAXN]; /* 存储多项式的系数 */
	for ( i=1; i<MAXN; i++ ) a[i] = 1/i; 
	a[0] = 1;
	
	run(f1, a, 1);
	run(f2, a, 2);

	return 0;
}
double f1( int n, double a[], double x )
{ 	
    int i;
	double p = a[0];
	for (i = 1; i <= n; i++)
	p += (a[i] * pow(x, i)); 
	return p;
}
double f2( int n, double a[], double x )
{ 
    int i;
	double p = a[n];
	for (i = n; i > 0; i --)
	p = a[i-1] + x * p;
	return p;
} 

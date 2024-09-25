#include <stdio.h>
#include <time.h>
#include <math.h>
clock_t start, stop; 
double duration;
#define MAXN 100000 /* 数据量 */
void PrintN1 ( int N );
void PrintN2 ( int N );
int main ()
{ 
    int i;
	double a[MAXN]; /* 存储多项式的系数 */
	for ( i=0; i<MAXN; i++ ) a[i] = (double)i; 
	start = clock();
	PrintN1(MAXN); 
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK; 
	printf("ticks1 = %f\n", (double)(stop - start));
	printf("duration1 = %6.2e\n", duration);
	start = clock();
	PrintN2(MAXN); 
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK; 
	printf("ticks2 = %f\n", (double)(stop - start));
	printf("duration2 = %6.2e\n", duration);
	return 0;
}
void PrintN1 ( int N )
{ 
    int i;
	for ( i = 1; i <= N; i ++ ){
		printf("%d\n", i );
	}
	return;
} 
void PrintN2 ( int N )
{ 
    if ( N ){
		PrintN2( N - 1 ); 
		printf("%d\n", N );
	}
	return;
} 

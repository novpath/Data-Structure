#include <stdio.h>
#include <time.h>
#include <math.h>
clock_t start, stop; 
double duration;
#define MAXN 10000 /* Êý¾ÝÁ¿ */
void PrintN1 ( int N );
void PrintN2 ( int N );
void run(void(*f)(int), int case_n)
{
	start = clock();
	(*f)(MAXN); 
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK; 
	printf("ticks%d = %f\n", case_n, (double)(stop - start));
	printf("duration%d = %6.2e\n", case_n, duration);
}

int main ()
{ 
	run(PrintN1, 1);
	getchar();
	system("cls");
	run(PrintN2, 2);
	
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

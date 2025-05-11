#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
clock_t start, stop; 
double duration;
#define MAXN 40000 /* 数据量 */
void PrintN1 ( int N , FILE *fptr);
void PrintN2 ( int N , FILE *fptr);
void run(void(*f)(int, FILE *), int case_n, FILE *fptr)
{
	start = clock();
	(*f)(MAXN, fptr); 
	stop = clock();
	duration = ((double)(stop - start))/CLK_TCK; 
	printf("ticks%d = %f\n", case_n, (double)(stop - start));
	printf("duration%d = %6.2e\n", case_n, duration);
}

int main ()
{ 
	FILE *fp;
	if((fp = fopen("result.txt", "a+")) == NULL){
		printf("Can not open the file!\n");
		exit(0);
	}
	run(PrintN1, 1, fp);
	run(PrintN2, 2, fp);
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
	
	return 0;
}
void PrintN1 ( int N , FILE *fptr)
{ 
    int i;
	for ( i = 1; i <= N; i ++ ){
		fprintf(fptr, "%d\n", i );
	}
	return;
} 
void PrintN2 ( int N, FILE *fptr)
{ 
    if ( N ){
		PrintN2( N - 1, fptr); 
		fprintf(fptr, "%d\n", N );
	}
	return;
} 

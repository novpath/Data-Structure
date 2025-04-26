#include <stdio.h>
#include <math.h>

int prime(int p)
{
    int isprime = 1;
    if (p <= 1) {
        isprime = 0;
    } else {
        for (int i = 2; i <= sqrt(p); i++) {
            if (p % i == 0) {
                isprime = 0;
                break;
            }
        }
    }

    return isprime;
}

int main()
{
	long n;
    int i;
	scanf("%ld", &n);
	int cnt = 0;
	int first = 1;
	printf("%d=", n);
	for (i = 2; i <= sqrt(n); i++) {
		while (n % i == 0 && prime(i)) {
			if (cnt == 0 && first == 0)
				printf("*"); 
			first = 0;
			n /= i;
			cnt++;
			if (cnt == 1)
				printf("%d", i);
			else if (cnt == 2)
				printf("^");
		}
		if (cnt > 1)
			printf("%d", cnt);
		cnt = 0;
	}
	if (first == 1)
		printf("%d", n);
	else if (n != 1)
		printf("*%d", n);

    return 0;
}


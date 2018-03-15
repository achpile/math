#include <stdio.h>
#include <stdlib.h>


/***********************************************************************
    * oddity

***********************************************************************/
unsigned oddity(unsigned long long int x, unsigned val = 0) {
	if (x % 2 == 0) return val;
	else return oddity((3*x+1)/2, val+1);
}


/***********************************************************************
    * dump_oddity

***********************************************************************/
unsigned dump_oddity(unsigned x) {
	for (unsigned i = 0; i < 10; i++)
		if (i < x) printf("+");
		else       printf(" ");

	printf(" [%u] ", x);
}


/***********************************************************************
    * collatz

***********************************************************************/
void collatz(unsigned long long int x, bool once) {
	unsigned long long k = x;

	if (k % 2) k  = (3*k+1)/2;
	else       k /= 2;

	if (once) {
		printf("(%llu)\n", k);
		return;
	}

	if (k == 1)
		return;

	collatz(k, false);
}



/***********************************************************************
    * MAIN

***********************************************************************/
int main() {
	for (unsigned long long int i = 1; i <= 100; i++) {
		printf("%4llu = ", i);
		dump_oddity(oddity(i));
		collatz(i, true);
	}

	return EXIT_SUCCESS;
}

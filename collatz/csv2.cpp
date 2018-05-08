#include <stdio.h>
#include <stdlib.h>

#define COUNT 255

/* ****************************************************************** */

void dump_bin(unsigned x) {
	printf("\"");

	for (int i = 15; i >= 0; i--)
		if (x & (1 << i)) printf("X");
		else              printf("_");

	printf("\"");
}

/* ****************************************************************** */

/***********************************************************************
    * oddity

***********************************************************************/
unsigned oddity(unsigned long long int x, unsigned val = 0) {
	if (x % 2 == 0) return val;
	else return oddity((3*x+1)/2, val+1);
}


/***********************************************************************
    * next

***********************************************************************/
unsigned next(unsigned x) {
	return 3*x+1;
}


/***********************************************************************
    * next2

***********************************************************************/
unsigned next2(unsigned x) {
	return next(x)/2;
}


/***********************************************************************
    * MAIN

***********************************************************************/
int main() {
	printf("NUM,ODDITY,N1,N2,\"bin NUM\",\"bin N1\",\"bin N2\"\n");
	for (unsigned i = 1; i < COUNT; i+=2) {
		printf("%u,%u,%u,%u,", i, oddity(i), next(i), next2(i));
		dump_bin(i); printf(",");
		dump_bin(next(i)); printf(",");
		dump_bin(next2(i)); printf("\n");
	}

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
    * DEFINES

***********************************************************************/
#define SIZE   3
#define POW    1
#define MAX    100



/***********************************************************************
    * Square

***********************************************************************/
struct Square {
	unsigned long long int data[SIZE][SIZE];
	unsigned long long int powd[SIZE][SIZE];


	void init();
	bool iterate();
	bool align();
	void pow();
	bool check();
	bool valid();

	void dump();
	void line();
};



/***********************************************************************
    * Square
    * init

***********************************************************************/
void Square::init() {
	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++)
			data[i][j] = 1;
}



/***********************************************************************
    * Square
    * iterate

***********************************************************************/
bool Square::iterate() {
	data[0][0]++;

	return align();
}



/***********************************************************************
    * Square
    * align

***********************************************************************/
bool Square::align() {
	bool increase = false;

	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++) {
			if (increase) {
				data[i][j]++;
				increase = false;
			}

			if (data[i][j] == MAX) {
				data[i][j] = 1;
				increase   = true;
			}
		}

	return !increase;
}



/***********************************************************************
    * Square
    * pow

***********************************************************************/
void Square::pow() {
	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++) {
			powd[i][j] = data[i][j];

			for (unsigned int k = 1; k < POW; k++)
				powd[i][j] *= data[i][j];
		}
}



/***********************************************************************
    * Square
    * check

***********************************************************************/
bool Square::check() {
	if (!valid()) return false;

	pow();

	unsigned long long int s1, s2, s3, s4, sum;

	sum = 0;
	s3  = 0;
	s4  = 0;

	for (unsigned int i = 0; i < SIZE; i++)
		sum += powd[i][0];

	for (unsigned int i = 0; i < SIZE; i++) {
		s1  = 0;
		s2  = 0;
		s3 += powd[i][i];
		s4 += powd[i][SIZE - i -1];

		for (unsigned int j = 0; j < SIZE; j++) {
			s1 += powd[i][j];
			s2 += powd[j][i];
		}

		if (sum != s1) return false;
		if (sum != s2) return false;
	}

	if (sum != s3) return false;
	if (sum != s4) return false;

	return true;
}



/***********************************************************************
    * Square
    * valid

***********************************************************************/
bool Square::valid() {
	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++)
			for (unsigned int k = 0; k < SIZE; k++)
				for (unsigned int l = 0; l < SIZE; l++)
					if (data[i][j] == data[k][l] && (i != k || j != l))
						return false;

	return true;
}



/***********************************************************************
    * Square
    * dump

***********************************************************************/
void Square::dump() {
	printf("\n   -== TABLE DUMP ==-\n\n");

	line();

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			printf("| %3llu ", data[i][j]);

		printf("|\n");
		line();
	}

	printf("\n\n");
}



/***********************************************************************
    * Square
    * line

***********************************************************************/
void Square::line() {
	for (int i = 0; i < SIZE; i++) printf("+-----");
	printf("+\n");
}



/***********************************************************************
    * MAIN

***********************************************************************/
int main() {
	Square a;

	a.init();

	do {
		if (a.check())
			a.dump();
	} while (a.iterate());

	return EXIT_SUCCESS;
}

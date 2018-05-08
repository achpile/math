#include <stdio.h>
#include <stdlib.h>

#define COUNT 255
#define SIZE  32

struct bin {
	bool digit;
	bool change;
};

struct num {
	bin m_num[SIZE];

	void reset();
	void zero();
	void change(int pos);
	void process();
	void init(unsigned x);
	void dump();
};

/* ****************************************************************** */

void num::reset() {
	for (int i = 0; i < SIZE; i++)
		m_num[i].change = false;
}

void num::zero() {
	for (int i = 0; i < SIZE; i++)
		m_num[i].digit = false;

	reset();
}

void num::change(int pos) {
	if (pos >= SIZE) return;

	if (m_num[pos].change) change(pos+1);

	m_num[pos].change = !m_num[pos].change;
}

void num::process() {
	reset();

	m_num[0].digit  = false;
	m_num[2].change = true;

	for (int i = 1; i < SIZE; i++) {
		if (m_num[i].digit ) {
			if (m_num[i].change) change(i+2);
			else                 change(i+1);
		}

		if (m_num[i].change) m_num[i].digit = !m_num[i].digit;
	}
}

void num::init(unsigned x) {
	zero();

	for (int i = 0; i < SIZE; i++)
		if (x & (1 << i)) m_num[i].digit = true;
		else              m_num[i].digit = false;
}

void num::dump() {
	for (int i = SIZE - 1; i >= 0; i--)
		if (m_num[i].digit) printf("X");
		else                printf("_");

	printf("\n");
}

/* ****************************************************************** */

void dump_bin(unsigned x) {
	for (int i = 31; i >= 0; i--)
		if (x & (1 << i)) printf("X");
		else              printf("_");

	printf("\n");
}

/* ****************************************************************** */

/***********************************************************************
    * next

***********************************************************************/
unsigned next(unsigned x) {
	return 3*x+1;
}


/***********************************************************************
    * MAIN

***********************************************************************/
int main(int argc, char **argv) {
	if (argc < 2) return EXIT_SUCCESS;

	num a;
	unsigned x = atoi(argv[1]);

	a.init(x);

	dump_bin(x);
	dump_bin(next(x));
	a.dump();
	a.process();
	a.dump();

	return EXIT_SUCCESS;
}

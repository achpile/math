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
	void process2();
	void init(unsigned x);
	void dump();
	void deeven();
	bool check();
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

void num::process2() {
	do {
		process();
		deeven();
		dump();
	} while(check());
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

	unsigned int x = 0;

	for (int i = 0; i < SIZE; i++)
		if (m_num[i].digit)
			x += (1 << i);

	printf(" (%u)\n", x);
}

bool num::check() {
	for (int i = 1; i < SIZE; i++)
		if (m_num[i].digit) return true;

	return false;
}

void num::deeven() {
	int i;

	for (i = 1; i < SIZE; i++)
		if (m_num[i].digit)
			break;

	for (int k = 0; k < SIZE - i; k++)
		m_num[k] = m_num[k+i];

	for (int k = SIZE - i; k < SIZE; k++)
		m_num[k].digit = false;
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
	a.dump();
	a.process2();

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>


#define COUNT 500
#define X     1000.0f
#define Y     500.0f


struct num {
	unsigned evenity;
	unsigned next;
};


sf::RenderWindow app;
sf::VertexArray  line(sf::Lines, 2);
num nums[COUNT];

/* ****************************************************************** */

/***********************************************************************
    * coordGetX

***********************************************************************/
float coordGetX(unsigned i) {
	return (X * i) / COUNT;
}

/***********************************************************************
    * coordGetY

***********************************************************************/
float coordGetY(unsigned i) {
	return Y - i * 25;
}

/* ****************************************************************** */

/***********************************************************************
    * renderEvenity

***********************************************************************/
void renderOddity(unsigned i) {
	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	line[0].position = sf::Vector2f(coordGetX(i), Y);
	line[1].position = sf::Vector2f(coordGetX(i), coordGetY(nums[i].evenity));

	app.draw(line);
}

/***********************************************************************
    * renderLink

***********************************************************************/
void renderLink(unsigned i) {
	if (i >= COUNT)
		return;

	if (nums[i].next >= COUNT)
		return;

	if (i % 2 == 1) return;

	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Green;

	line[0].position = sf::Vector2f(coordGetX(nums[i].next), coordGetY(nums[nums[i].next].evenity));
	line[1].position = sf::Vector2f(coordGetX(i), coordGetY(nums[i].evenity));

	app.draw(line);
}

/* ****************************************************************** */

/***********************************************************************
    * evenity

***********************************************************************/
unsigned evenity(unsigned long long int x, unsigned val = 0) {
	if (x % 2) return 0;

	while (x % 2 == 0)
		x /= 2;

	if (x == 1) return val;

	while (x % 2)
		x = (3*x + 1) / 2;

	return evenity(x, val + 1);
}


/***********************************************************************
    * next

***********************************************************************/
unsigned next(unsigned x) {
	if (x % 2) return 0;

	while (x % 2 == 0)
		x /= 2;

	if (x == 1) return 1;

	while (x % 2)
		x = (3*x + 1) / 2;

	return x;
}


/***********************************************************************
    * MAIN

***********************************************************************/
int main() {
	for (unsigned i = 1; i < COUNT; i++) {
		nums[i].evenity = evenity(i);
		nums[i].next    = next(i);
	}

	for (unsigned i = 1; i < COUNT; i++)
		if (i%2==0)
		if (evenity(i) <= evenity(next(i)))
			printf("%u => %u\n", i, next(i));


	app.create(sf::VideoMode(X, Y), "Collatz");

	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.clear();

		for (unsigned i = 1; i < COUNT; i++) {
			renderOddity(i);
			renderLink(i);
		}

		app.display();
	}


	return EXIT_SUCCESS;
}

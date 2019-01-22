#include <string>
#include <sstream>
#include <math.h>
#include <unistd.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/* ****************************************************************** */

#define SIZE      250
#define SCALE     4
#define FRAMESKIP 100
#define SLEEP     0

/* ****************************************************************** */

struct cell {
	sf::Color color;
	bool      turnRight;

	cell(sf::Color _color, bool _turnRight) {color = _color; turnRight = _turnRight;};
};

/* ****************************************************************** */

sf::RenderWindow   window;
sf::RenderTexture  tex;
sf::Sprite         spr;
sf::RectangleShape square;
sf::Vector2i       pos;
sf::Vector2i       dir;
sf::Color          map[SIZE][SIZE];

std::vector<cell> cells;

bool              finished;
int               frame;

/* ****************************************************************** */

void events() {
	sf::Event event;

	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}

/* ****************************************************************** */

void turn(bool turnRight) {
	if (turnRight) {
		     if (dir == sf::Vector2i( 0, -1)) dir = sf::Vector2i( 1,  0);
		else if (dir == sf::Vector2i( 1,  0)) dir = sf::Vector2i( 0,  1);
		else if (dir == sf::Vector2i( 0,  1)) dir = sf::Vector2i(-1,  0);
		else if (dir == sf::Vector2i(-1,  0)) dir = sf::Vector2i( 0, -1);
	} else {
		     if (dir == sf::Vector2i( 0, -1)) dir = sf::Vector2i(-1,  0);
		else if (dir == sf::Vector2i(-1,  0)) dir = sf::Vector2i( 0,  1);
		else if (dir == sf::Vector2i( 0,  1)) dir = sf::Vector2i( 1,  0);
		else if (dir == sf::Vector2i( 1,  0)) dir = sf::Vector2i( 0, -1);
	}
}

/* ****************************************************************** */

void render(int x, int y, sf::Color color) {
	square.setFillColor(color);
	square.setPosition(x * SCALE, y * SCALE);
	tex.draw(square);
}

/* ****************************************************************** */

void step() {
	pos += dir;

	if (pos.x < 0 || pos.y < 0 || pos.x >= SIZE || pos.y >= SIZE) {
		finished = true;
		return;
	}

	unsigned int  ind;

	for (unsigned int i = 0; i < cells.size(); i++)
		if (cells[i].color == map[pos.x][pos.y])
			ind = i;

	ind++;

	if (ind == cells.size())
		ind = 0;

	map[pos.x][pos.y] = cells[ind].color;
	turn(cells[ind].turnRight);

	render(pos.x, pos.y, cells[ind].color);
}

/* ****************************************************************** */

void initSequence() {
	cells.push_back(cell(sf::Color::White, false));
	cells.push_back(cell(sf::Color::Red  , true));
}

/* ****************************************************************** */

void initMap() {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			map[i][j] = cells[0].color;

	tex.clear(cells[0].color);
}

/* ****************************************************************** */

int main() {
	window.create(sf::VideoMode(SIZE * SCALE, SIZE * SCALE), "My window", sf::Style::Default, sf::ContextSettings(0,0,2));
	window.setVerticalSyncEnabled(true);

	tex.create(SIZE * SCALE, SIZE * SCALE, true);
	tex.setRepeated(false);
	tex.setActive(true);
	tex.setSmooth(false);

	spr.setPosition(0, 0);
	spr.setTexture(tex.getTexture());

	pos = sf::Vector2i(SIZE / 2, SIZE / 2);
	dir = sf::Vector2i(  0,  -1);

	finished = false;
	frame    = 0;

	square.setSize(sf::Vector2f(SCALE, SCALE));

	initSequence();
	initMap();

	while (window.isOpen()) {
		events();

		while (frame++ < FRAMESKIP)
			if (!finished)
				step();

		frame = 0;

		window.clear(sf::Color::Black);
		window.draw(spr);
		window.display();

		usleep(SLEEP);
	}

	return 0;
}

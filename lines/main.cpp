#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/* ****************************************************************** */

#define RADIUS     475
#define WSIZE      ((RADIUS + 25) * 2)
#define CENTER     (WSIZE / 2)
#define PCOUNT     128
#define COUNT      5500
#define TRANSPAR   20
#define PI         3.1415926f
#define SPEED      0.2f
#define START      0.0f

/* ****************************************************************** */

sf::RenderWindow window;
sf::CircleShape  circle;
sf::VertexArray  line;
sf::Clock        cloc;

long             lastClock;
float            frameClock;

/* ****************************************************************** */

void events() {
	sf::Event event;

	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();

	long currentClock = cloc.getElapsedTime().asMilliseconds();
	if (currentClock - lastClock < 15) return;

	frameClock = (currentClock - lastClock) / 1000.0;
	lastClock  = currentClock;

}

/* ****************************************************************** */

sf::Vector2f getOutPos(float index) {
	float angle = 2.0f * PI * index / COUNT;
	return sf::Vector2f(CENTER + RADIUS * cos(angle), CENTER + RADIUS * sin(angle));
}

/* ****************************************************************** */

void drawCircle(sf::Vector2f pos, float radius, sf::Color fill, sf::Color out = sf::Color::Transparent, size_t pointCount = 32) {
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(pos);
	circle.setFillColor(fill);
	circle.setOutlineColor(out);
	circle.setOutlineThickness(1.0f);
	circle.setPointCount(pointCount);

	window.draw(circle);
}

/* ****************************************************************** */

void drawLine(sf::Vector2f a, sf::Vector2f b) {
	line[0].position = a;
	line[1].position = b;

	window.draw(line);
}

/* ****************************************************************** */

void drawLine(float i1, float i2) {
	drawLine(getOutPos(i1), getOutPos(i2));
}

/* ****************************************************************** */

void render(float k) {
	drawCircle(sf::Vector2f(CENTER,CENTER), RADIUS, sf::Color::Transparent, sf::Color::White, PCOUNT);

	for (int i = 0; i < COUNT; i++)
		drawCircle(getOutPos(i), 1, sf::Color::Transparent, sf::Color::Cyan, 16);

	for (int i = 0; i < COUNT; i++)
		drawLine(i, (float)i * k);
}

/* ****************************************************************** */

int main() {
	float k = START;

	window.create(sf::VideoMode(WSIZE, WSIZE), "My window", sf::Style::Default, sf::ContextSettings(0,0,2));
	window.setVerticalSyncEnabled(true);
	line = sf::VertexArray(sf::Lines, 2);

	line[0].color = sf::Color(255,0,0,TRANSPAR);
	line[1].color = sf::Color(255,0,0,TRANSPAR);

	lastClock = cloc.getElapsedTime().asMilliseconds();

	while (window.isOpen()) {
		events();

		window.clear(sf::Color::Black);
		render(k);
		window.display();

		k += frameClock * SPEED;
	}

	return 0;
}

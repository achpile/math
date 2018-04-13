#include "headers.hpp"

/**********************************************************************/

struct TestNode {
	sf::Vector2i pos;
	unsigned int power;

	TestNode(sf::Vector2i _pos, unsigned int _power) {pos = _pos; power = _power;};
};

/**********************************************************************/

std::vector<TestNode*> nodes;
sf::RenderWindow *app;
sf::CircleShape  *shape;
al::AlgoGraph *graph;
sf::VertexArray line(sf::Lines, 2);

/**********************************************************************/
/*
	exits - is the locations that must be connected by dungeons
	deadends - is the locations to be generated (probably treasure rooms
	           or quest shops, or just nothing)
	len - count of midlocations
*/
/**********************************************************************/

void generate(int exits, int deadends, int len) {
	deleteList(nodes);

	for (int i = 0; i < exits; i++)
		nodes.push_back(new TestNode(sf::Vector2i(100 + rand() % 600, 100 + rand() % 400), 1));

	for (int i = 0; i < deadends; i++)
		nodes.push_back(new TestNode(sf::Vector2i(100 + rand() % 600, 100 + rand() % 400), 1));

	for (int i = 0; i < len; i++)
		nodes.push_back(new TestNode(sf::Vector2i(100 + rand() % 600, 100 + rand() % 400), 2));

	for (int i = 0; i < exits + deadends - 2; i++)
		nodes.push_back(new TestNode(sf::Vector2i(100 + rand() % 600, 100 + rand() % 400), 3));


	graph->clear();
	for (unsigned int i = 0; i < nodes.size(); i++) graph->addNode(nodes[i]->power);
	graph->generate();
}

/**********************************************************************/

void renderNodes() {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		shape->setPosition(sf::Vector2f(nodes[i]->pos));
		shape->setRadius(nodes[i]->power * 2);
		shape->setOrigin(nodes[i]->power * 2, nodes[i]->power * 2);
		app->draw(*shape);
	}

	for (unsigned int i = 0; i < graph->edges.size(); i++) {
		line[0].position = sf::Vector2f(nodes[graph->edges[i]->A]->pos);
		line[1].position = sf::Vector2f(nodes[graph->edges[i]->B]->pos);

		app->draw(line);
	}
}


/**********************************************************************/

void render() {
	app->clear();
	renderNodes();
	app->display();


	sf::Event event;
	while (app->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			app->close();
		if (event.type == sf::Event::MouseButtonReleased)
			generate(2, 1, 5);
	}
}

/**********************************************************************/

int main() {
	graph = new al::AlgoGraph();
	app   = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Graph", sf::Style::Close);
	srand(time(NULL));

	shape = new sf::CircleShape();
	shape->setFillColor(sf::Color::Black);
	shape->setOutlineThickness(1);
	shape->setOutlineColor(sf::Color::White);

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	while (app->isOpen()) render();

	deleteList(nodes);
	delete app;
	delete shape;
	delete graph;
}

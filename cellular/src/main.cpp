#include "headers.hpp"
// 40 40 30 8 4 1

int main(int argc, char **argv) {
	al::AlgoMap *map = new al::AlgoMap();

	srand(time(NULL));
	gen(map, sf::Vector2i(30, 30));

	delete map;
	return EXIT_SUCCESS;
}

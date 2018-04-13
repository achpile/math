/***********************************************************************
     * File       : main.cpp
     * Created    : Feb 16, 2015
     * Copyright  : (C) 2015 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"


static bool checkPos(std::vector<sf::Vector2i> *list, sf::Vector2i pos) {
	for (unsigned int i = 0; i < list->size(); i++)
		if ((*list)[i] == pos)
			return false;

	return true;
}

static sf::Vector2i getNextTile(al::AlgoMap *map) {
	std::vector<sf::Vector2i> list;

	for (int i = 1; i < map->size.x - 1; i++)
		for (int j = 1; j < map->size.y - 1; j++)
			if (!map->tiles[i][j].wall)
				if (!map->canMove(sf::Vector2i(i, j), al::dUp)    ||
				    !map->canMove(sf::Vector2i(i, j), al::dDown)  ||
				    !map->canMove(sf::Vector2i(i, j), al::dLeft)  ||
				    !map->canMove(sf::Vector2i(i, j), al::dRight))
					if (checkPos(&list, sf::Vector2i(i, j)))
						list.push_back(sf::Vector2i(i, j));

	return list[rand() % list.size()];
}


static void generateLocation(al::AlgoMap *map, unsigned int count) {
	sf::Vector2i pos;

	map->init(count, count);
	map->tiles[map->size.x / 2][map->size.y / 2].wall = true;

	for (unsigned int i = 0; i < count - 1; i++) {
		pos = getNextTile(map);
		map->tiles[pos.x][pos.y].wall = true;
	}
}


/***********************************************************************
     * Main function

***********************************************************************/
int main() {
	al::AlgoMap *map = new al::AlgoMap();

	srand(time(NULL));
	generateLocation(map, 10);

	for (int i = 0; i < map->size.x; i++) {
		for (int j = 0; j < map->size.y; j++)
			if (map->tiles[i][j].wall) printf("#");
			else printf(" ");

		printf("\n");
	}

	delete map;
	return EXIT_SUCCESS;
}

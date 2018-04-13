/***********************************************************************
     * File       : algo_map.cpp
     * Created    : Feb 22, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * AlgoMap
     * constructor

***********************************************************************/
al::AlgoMap::AlgoMap() {
	size = sf::Vector2i(0, 0);
}



/***********************************************************************
     * AlgoMap
     * destructor

***********************************************************************/
al::AlgoMap::~AlgoMap() {
	for (int i = 0; i < size.x; delete tiles[i++]);
	delete tiles;
}



/***********************************************************************
     * AlgoMap
     * init

***********************************************************************/
void al::AlgoMap::init(int sizeX, int sizeY) {
	size = sf::Vector2i(sizeX, sizeY);

	tiles = new al::AlgoTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new al::AlgoTile[sizeY];

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			tiles[i][j].wall = false;

	reset();
}



/***********************************************************************
     * AlgoMap
     * reset

***********************************************************************/
void al::AlgoMap::reset() {
	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
			tiles[i][j].value = 0;
}



/***********************************************************************
     * AlgoMap
     * canMove

***********************************************************************/
bool al::AlgoMap::canMove(sf::Vector2i pos, al::Direction dir) {
	sf::Vector2i newPos = pos + getDirection(dir);

	if (newPos.x <  0     ) return false;
	if (newPos.x >= size.x) return false;
	if (newPos.y <  0     ) return false;
	if (newPos.y >= size.y) return false;

	return !tiles[newPos.x][newPos.y].wall;
}

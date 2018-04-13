/***********************************************************************
     * File       : algo_map.hpp
     * Created    : Feb 22, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ALGO_MAP
#define __ALGO_MAP


namespace al {
	struct AlgoTile {
		bool wall;
		int  value;
	};


	struct AlgoMap {
		al::AlgoTile **tiles;
		sf::Vector2i   size;


		 AlgoMap();
		~AlgoMap();

		void init(int sizeX, int sizeY);
		void reset();
		bool canMove(sf::Vector2i pos, al::Direction dir);
	};
}

#endif

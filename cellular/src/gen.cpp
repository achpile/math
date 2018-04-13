#include "headers.hpp"

// 40 40 30 8 4 1

struct generation_params {
		int r1_cutoff, r2_cutoff;
		int reps;
		int fillprob;
}; 


bool randpick(generation_params *params) {
	if(rand() % 100 < params->fillprob) return true;
	else                                return false;
}


void initmap(al::AlgoMap *grid1, al::AlgoMap *grid2, al::AlgoMap *map, sf::Vector2i size, generation_params *params) {
	map->init(size.x, size.y);

	grid1->init(size.x + 2, size.y + 2);
	grid2->init(size.x + 2, size.y + 2);


	for(int i = 0; i < grid1->size.x; i++)
		for(int j = 0; j < grid1->size.y; j++) {
			grid1->tiles[i][j].wall = randpick(params);
			grid2->tiles[i][j].wall = true;
		}
 
	for (int i = 0; i < grid1->size.y; i++)
		grid1->tiles[i][0].wall = grid1->tiles[i][grid1->size.y - 1].wall = true;

	for (int i = 0; i < grid1->size.x; i++)
		grid1->tiles[0][i].wall = grid1->tiles[grid1->size.x - 1][i].wall = true;
}

void generation(al::AlgoMap *grid1, al::AlgoMap *grid2, generation_params *params) {
	int adjcount_r1;
	int adjcount_r2;

	for(int x = 1; x < grid1->size.x - 1; x++) for(int y = 1; y < grid1->size.y - 1; y++) {
		adjcount_r1 = 0;
		adjcount_r2 = 0;

		for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++)
			if(!grid1->tiles[x + dx][y + dy].wall)
				adjcount_r1++;

		for (int dx = x - 2; dx <= x + 2; dx++) for (int dy = y - 2; dy <= y + 2; dy++) {
			if(abs(dy - y) == 2 && abs(x - dx) == 2)
				continue;

			if(dx < 0 || dy < 0 || dx >= grid1->size.x || dy >= grid1->size.y)
				continue;

			if(!grid1->tiles[dx][dy].wall)
				adjcount_r2++;
		}

		if(adjcount_r1 >= params->r1_cutoff || adjcount_r2 <= params->r2_cutoff)
			grid2->tiles[x][y].wall = true;
		else
			grid2->tiles[x][y].wall = false;
	}

	for (int x = 1; x < grid1->size.x - 1; x++)
		for (int y = 1; y < grid1->size.y - 1; y++)
			grid1->tiles[x][y].wall = grid2->tiles[x][y].wall;
}

void printmap(al::AlgoMap *map) {
	for(int i = 0; i < map->size.x; i++) {
		for(int j = 0; j < map->size.y; j++)
			if (map->tiles[i][j].wall) putchar('#');
			else                       putchar('.');

		putchar('\n');
	}
}

void copyMap(al::AlgoMap *map, al::AlgoMap *grid1) {
	for (int x = 0; x < map->size.x; x++)
		for (int y = 0; y < map->size.y; y++)
			map->tiles[x][y].wall = grid1->tiles[x + 1][y + 1].wall;
}
 
void gen(al::AlgoMap *map, sf::Vector2i size) {
	al::AlgoMap *grid1 = new al::AlgoMap();
	al::AlgoMap *grid2 = new al::AlgoMap();
 
	generation_params *params = new generation_params();
	params->r1_cutoff = 8;
	params->r2_cutoff = 4;
	params->reps      = 1;
	params->fillprob  = 30;

	initmap(grid1, grid2, map, size, params);
	generation(grid1, grid2, params);
	copyMap(map, grid1);

	printmap(map);

	delete grid1;
	delete grid2;
	delete params;
}

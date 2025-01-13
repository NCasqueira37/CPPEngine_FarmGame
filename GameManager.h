#pragma once
#include <vector>
#include "Tile.h"
#include "Plant.h"

class GameManager
{

public:
	std::vector<Tile> tiles;
	std::vector<Plant> plants;
	Tile::TileType selectedTileType = Tile::TileType::background;
};


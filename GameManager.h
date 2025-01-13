#pragma once
#include <vector>
#include "Tile.h"

class GameManager
{

public:
	std::vector<Tile> tiles;
	Tile::TileType selectedTileType;
};


#pragma once
#include <iostream>

class Level;

enum TileType {
	background,
	water,
	grass,
	wet
};

class Tile
{
	TileType tileType = TileType::background;

public:
	int x, y;
	int tileSize = 0;

	Tile(int x, int y, int tileSize) : x(x), y(y), tileSize(tileSize) {};

	void setTileType(const TileType tileType) { this->tileType = tileType; };
	static void setTileType(Tile& tile, const TileType tileType) { tile.tileType = tileType; };
	static void setTileWet(Tile& tile, Level& level);
	static void updateTileWet(Level& level);

	const TileType getTileType() const { return tileType; };
};


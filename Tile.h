#pragma once
#include <iostream>
#include <vector>

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
	bool hasPlant = false;

	Tile() :x(-50), y(-50) {};
	Tile(int x, int y, int tileSize) : x(x), y(y), tileSize(tileSize) {};

	void setTileType(const TileType tileType) { this->tileType = tileType; };
	static void setTileType(Tile& tile, const TileType tileType) { tile.tileType = tileType; };
	static void setTileWet(Tile& tile, Level& level);
	static void updateTileWet(Level& level);
	static Tile getTileFromMouse(std::vector<Tile> tiles);

	const TileType getTileType() const { return tileType; };
};


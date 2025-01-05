#pragma once

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

	void setTileId(const TileType tileType) { this->tileType = tileType; };
	static void setTileId(Tile& tile, const TileType tileType) { tile.tileType = tileType; };
	const TileType getTileId() const { return tileType; };
};


#pragma once
#include "SDL.h"
#include <vector>


class Tile
{
	
public:
	enum TileType {
		background,
		grass,
		water,
	};

	int x, y;
	TileType tileType = background;
	bool isWet = false;

	Tile(int x, int y, std::vector<Tile>& tiles);

	static void createTiles(int w, int h, int tileSize, std::vector<Tile>& tiles);
	void draw(SDL_Renderer* renderer, int tileSize) const;
	static void placeTile(int x, int y, int tileSize, TileType tileType, std::vector<Tile>& tiles);
	static void checkForNearbyWater(int x, int y, std::vector<Tile>& tiles);
};


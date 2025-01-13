#pragma once
#include "SDL.h"
#include <vector>


class Plant;

class Tile
{
	
public:
	enum TileType {
		background,
		grass,
		water,
	};

	int x = 0, y = 0;
	TileType tileType = background;
	bool isWet = false;
	bool hasPlant = false;

	Tile() = default;
	Tile(int x, int y, std::vector<Tile>& tiles);

	static void createTiles(int w, int h, int tileSize, std::vector<Tile>& tiles);
	void draw(SDL_Renderer* renderer, int tileSize) const;
	static void placeTile(int x, int y, int tileSize, TileType tileType, std::vector<Tile>& tiles, std::vector<Plant>& plants);
	static void checkForNearbyWater(int x, int y, std::vector<Tile>& tiles);
	static bool checkTileIsWet(int x, int y, int tileSize, std::vector<Tile>& tiles);
	static bool checkTileHasPlant(int x, int y, int tileSize, std::vector<Tile>& tiles);
	static Tile& getTileOverMouse(int x, int y, int tileSize, std::vector<Tile>& tiles);

	// Function to make sure only grass tiles can be wet
	static void checkWetTiles(std::vector<Tile>& tiles);
};


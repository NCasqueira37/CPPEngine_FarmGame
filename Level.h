#pragma once
#include <vector>
#include "SDL.h"
#include "Tile.h"
#include <iostream>

class Level
{
public:
	std::vector<Tile> tiles;
	TileType selectedTile = TileType::background;

	Level() = default;
	
	void createTiles(int width, int height, int tileSize);
	void drawTiles(SDL_Renderer* renderer, int width, int height, int tileSize);
};
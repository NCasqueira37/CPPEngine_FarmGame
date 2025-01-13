#pragma once
#include "SDL.h"
#include <vector>
#include <iostream>
#include "Tile.h"


class Plant
{

public:
	int x = 0, y = 0;

	SDL_Texture* texture = nullptr;
	SDL_Rect rect{};

	Plant(int x, int y, int tileSize, SDL_Texture* texture, std::vector<Plant>& plants, std::vector<Tile>& tiles);
	void draw(SDL_Renderer* renderer);

	// Remove plant if its not under a wet tile
	static void checkPlantOverTile(std::vector<Tile>& tiles, std::vector<Plant>& plants);
};


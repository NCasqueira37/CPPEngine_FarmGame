#pragma once
#include "SDL.h"
#include <vector>
#include <iostream>
#include "Tile.h"
#include "RanNum.h"


class Plant
{

public:
	int x = 0, y = 0;

	SDL_Texture* texture = nullptr;
	SDL_Rect rect{};

	// Time and growth variables
	int spawnSize = 10;
	Uint64 startTime = SDL_GetTicks64();
	Uint64 currentTime = SDL_GetTicks64();
	int ranGrowthTime = RanNum::ranInt(3, 6);
	bool isGrown = false;

	Plant(int x, int y, int tileSize, SDL_Texture* texture, std::vector<Plant>& plants, std::vector<Tile>& tiles);
	void draw(SDL_Renderer* renderer);

	// Remove plant if its not under a wet tile
	static void checkPlantOverTile(std::vector<Tile>& tiles, std::vector<Plant>& plants);

	// get plant over mouse
	static Plant getPlantOverMouse(int x, int y, int tileSize, std::vector<Plant>& plants);

	// Harvest plant when fully grown
	static bool harvestPlant(int x, int y, std::vector<Plant>& plants, std::vector<Tile>& tiles);

	// grow plant after a certain time
	void growPlant();
	void update(float deltaTime);
};


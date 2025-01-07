#pragma once
#include "SDL.h"
#include <string>
#include <vector>
#include "TextureManager.h"

class Plant
{
	std::string id;
	SDL_Rect rect;
	
public:
	static std::vector<Plant> plants;
	int x = 0;
	int y = 0;

	Plant();
	Plant(int x, int y, std::string id, int tileSize);
	void drawPlant(SDL_Renderer* renderer, TextureManager& textureManager);
	void setPlantId(std::string id) { this->id = id; };
	std::string getPlantId() { return id; };
};
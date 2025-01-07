#include "Plant.h"

std::vector<Plant> Plant::plants;
Plant::Plant() {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	Plant::plants.push_back(*this);
}

Plant::Plant(int x, int y, std::string id, int tileSize){
	this->id = id;
	rect.x = x;
	rect.y = y;
	rect.w = tileSize;
	rect.h = tileSize;
	Plant::plants.push_back(*this);
}

void Plant::drawPlant(SDL_Renderer* renderer, TextureManager& textureManager) {
	if (textureManager.getTexture(id) != nullptr) {
		SDL_RenderCopy(renderer, textureManager.getTexture(id), NULL, &rect);
	}
	else {
		std::cout << "Problem drawing plant\n";
	}
}
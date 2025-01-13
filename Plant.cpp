#include "Plant.h"


Plant::Plant(int x, int y, int tileSize, SDL_Texture* texture, std::vector<Plant>& plants, std::vector<Tile>& tiles) {
	this->x = -50;
	this->y = -50;
	
	int xTilePos = x / tileSize;
	int yTilePos = y / tileSize;

	// Check if the tile is wet and has a plant
	bool isTileWet = Tile::checkTileIsWet(xTilePos, yTilePos, 50, tiles);
	bool hasPlant = Tile::checkTileHasPlant(xTilePos, yTilePos, 50, tiles);

	if (isTileWet && !hasPlant) {
		this->x = xTilePos;
		this->y = yTilePos;
		this->texture = texture;

		// Set tile bool to hasPlant
		Tile::getTileOverMouse(x, y, tileSize, tiles).hasPlant = true;

		rect.x = xTilePos * tileSize;
		rect.y = yTilePos * tileSize;
		rect.w = tileSize;
		rect.h = tileSize;
		plants.push_back(*this);

		std::cout << "Placed plant\n";
	}
}


void Plant::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Plant::checkPlantOverTile(std::vector<Tile>& tiles, std::vector<Plant>& plants) {
	// check every tile
	for (Tile& t : tiles) {
		// check if the tile is not grass and is wet
		if (t.tileType != Tile::TileType::grass && t.isWet == true) {
			t.isWet = false;
		}
	}
	for (Tile& t : tiles) {
		for (auto i = plants.begin(); i != plants.end();) {
			if (t.isWet == false && i->x == t.x && i->y == t.y) {
				// removes the plant from iterator
				i = plants.erase(i);
			}
			else {
				// if no removel, increment
				++i;
			}
		}
	}
}
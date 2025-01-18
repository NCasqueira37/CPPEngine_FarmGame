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

		// Add offset to plants
		double offset = RanNum::ranDouble(-4, 4);

		rect.x = (xTilePos * tileSize) + (int)offset;
		rect.y = (yTilePos * tileSize) + (int)offset;
		rect.w = tileSize - spawnSize;
		rect.h = tileSize - spawnSize;
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

				// set has plant bool to false when a plant is removed
				t.hasPlant = false;
			}
			else {
				// if no removel, increment
				++i;
			}
		}
	}
}


void Plant::growPlant() {
	if (isGrown == false) {
		currentTime = SDL_GetTicks64();
		if ((currentTime - startTime) / 1000 > ranGrowthTime) {
			rect.w += spawnSize;
			rect.h += spawnSize;

			isGrown = true;

			// resets the timer
			startTime = currentTime;
		}
	}
	
}


void Plant::update(float deltaTime) {
	growPlant();
}


bool Plant::harvestPlant(int x, int y, std::vector<Plant>& plants, std::vector<Tile>& tiles) {
	bool result = false;
	Tile tile = Tile::getTileOverMouse(x, y, 50, tiles);
	if (tile.hasPlant) {
		Plant plant = getPlantOverMouse(x, y, 50, plants);
		if (plant.isGrown) {
			for (auto it = plants.begin(); it != plants.end();) {
				if (it->x == plant.x && it->y == plant.y) {
					it = plants.erase(it);
					result = true;
				}
				else {
					++it;
				}
			}
		}
	}
	return result;
}


Plant Plant::getPlantOverMouse(int x, int y, int tileSize, std::vector<Plant>& plants) {
	int xTilePos = x / tileSize;
	int yTilePos = y / tileSize;
	bool foundPlant = false;

	for (Plant& p : plants) {
		if (p.x == xTilePos && p.y == yTilePos && !foundPlant) {
			foundPlant = true;
			return p;
		}
	}
}
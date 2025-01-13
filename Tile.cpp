#include "Tile.h"
#include <iostream>
#include "Plant.h"


Tile::Tile(int x, int y, std::vector<Tile>& tiles) {
	this->x = x;
	this->y = y;
	tiles.push_back(*this);
}


void Tile::createTiles(int w, int h, int tileSize, std::vector<Tile>& tiles) {
	for (int y = 0; y < h / tileSize; y++) {
		for (int x = 0; x < w / tileSize; x++) {
			Tile(x, y, tiles);
		}
	}
}


void Tile::draw(SDL_Renderer* renderer, int tileSize) const {
	SDL_Rect rect{ x * tileSize, y * tileSize, tileSize, tileSize };
	bool dark = ((x + y) % 2 == 0);

	switch (tileType)
	{
	case TileType::background:
		if (dark) {
			SDL_SetRenderDrawColor(renderer, 51, 24, 50, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 216, 30, 91, 255);
		}
		break;

	case TileType::grass:
		if (dark) {
			SDL_SetRenderDrawColor(renderer, 0, 110, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
		}
		
		if (isWet) {
			SDL_SetRenderDrawColor(renderer, 0, 128 / 2, 0, 255);
		}
		break;

	case TileType::water:
		SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
		break;

	default:
		break;
	}
	
	SDL_RenderFillRect(renderer, &rect);
}


void Tile::placeTile(int x, int y, int tileSize, TileType tileType, std::vector<Tile>& tiles, std::vector<Plant>& plants) {
	int tempX = x / tileSize;
	int tempY = y / tileSize;

	for (Tile& t : tiles) {
		if (tempX == t.x && tempY == t.y && t.tileType != tileType) {
			t.tileType = tileType;
			std::cout << "Tile Changed\n";

			checkForNearbyWater(tempX, tempY, tiles);
			checkWetTiles(tiles);
			Plant::checkPlantOverTile(tiles, plants);
		}
	}
}


void Tile::checkForNearbyWater(int x, int y, std::vector<Tile>& tiles) {
	// how far to look for water nearby in tile units
	int distance = 1;

	// loop through grass tiles and make them wet if a water tile is nearby
	for (Tile& grassTile : tiles) {
		if (grassTile.tileType == TileType::grass) {
			bool foundWater = false;
			for (int x1 = grassTile.x - distance; x1 <= grassTile.x + distance; x1++) {
				for (int y1 = grassTile.y - distance; y1 <= grassTile.y + distance; y1++) {
					// loop through the nearby tiles
					for (Tile& nearbyTile : tiles) {
						// Check if any nearby tiles are water
						if (nearbyTile.x == x1 && nearbyTile.y == y1 && foundWater == false) {
							if (nearbyTile.tileType == TileType::water) {
								foundWater = true;
							}
						}
					}
				}
			}
			grassTile.isWet = foundWater;
		}
	}
}


bool Tile::checkTileIsWet(int x, int y, int tileSize, std::vector<Tile>& tiles) {
	bool result = false;
	for (Tile& t : tiles) {
		if (t.x == x && t.y == y && result == false) {
			if (t.isWet == true) {
				result = true;
			}
		}
	}
	return result;
}


bool Tile::checkTileHasPlant(int x, int y, int tileSize, std::vector<Tile>& tiles) {
	bool result = false;
	for (Tile& t : tiles) {
		if (t.x == x && t.y == y && result == false) {
			if (t.hasPlant == true) {
				result = true;
			}
		}
	}
	return result;
}


Tile& Tile::getTileOverMouse(int x, int y, int tileSize, std::vector<Tile>& tiles) {
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	mouseX /= tileSize;
	mouseY /= tileSize;
	for (Tile& t : tiles) {
		if (mouseX == t.x && mouseY == t.y) {
			return t;
		}
	}
}


void Tile::checkWetTiles(std::vector<Tile>& tiles) {
	for (Tile& t : tiles) {
		if (t.tileType != TileType::grass && t.isWet == true) {
			t.isWet = false;
		}
	}
}
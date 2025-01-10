#include "Tile.h"
#include "Level.h"

void Tile::setTileWet(Tile& tile, Level& level) {
	// if the tile is water, make the surrounding tiles wet
	if (tile.getTileType() == TileType::water) {
		int distance = 1;
		for (int x1 = tile.x - distance; x1 <= tile.x + distance; x1++) {
			for (int y1 = tile.y - distance; y1 <= tile.y + distance; y1++) {
				for (Tile& t : level.tiles) {
					if (t.getTileType() == TileType::grass) {
						if (t.x == x1 && t.y == y1) {
							t.setTileType(TileType::wet);
						}
					}
				}
			}
		}
	}
}


void Tile::updateTileWet(Level& level) {
	for (Tile& tile : level.tiles) {
		if (tile.getTileType() == TileType::water) {
			int distance = 1;
			for (int x1 = tile.x - distance; x1 <= tile.x + distance; x1++) {
				for (int y1 = tile.y - distance; y1 <= tile.y + distance; y1++) {
					for (Tile& t : level.tiles) {
						if (t.getTileType() == TileType::grass) {
							if (t.x == x1 && t.y == y1) {
								t.setTileType(TileType::wet);
							}
						}
					}
				}
			}
		}
		else if (tile.getTileType() != TileType::wet && tile.hasPlant == true) {
			
			tile.hasPlant = false;
		}
	}
}


Tile Tile::getTileFromMouse(std::vector<Tile> tiles) {
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	for (Tile& t : tiles) {

		int xTileSize = t.x * t.tileSize;
		int yTileSize = t.y * t.tileSize;

		if (x > xTileSize && x < xTileSize + t.tileSize &&
			y > yTileSize && y < yTileSize + t.tileSize) {
			std::cout << "x: " << t.x << ", y: " << t.y << std::endl;
			return t;
		}
	}
	return Tile();
}
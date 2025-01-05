#include "Level.h"

void Level::createTiles(int width, int height, int tileSize) {
	int amountOfTiles = (width + height) / tileSize;
	int index = 0;
	while (index < amountOfTiles) {
		for (size_t x = 0; x < width/tileSize; x++)
		{
			for (size_t y = 0; y < height / tileSize; y++)
			{
				Tile t((int)x, (int)y, tileSize);
				tiles.push_back(t);
				index++;
			}
		}
	}
}
void Level::drawTiles(SDL_Renderer* renderer, int width, int height, int tileSize) {
	for (Tile& t : tiles) {
		bool dark = ((t.x + t.y) % 2 == 0);
		switch (t.getTileId())
		{
		case TileType::background:
			if (dark) {
				SDL_SetRenderDrawColor(renderer, 170, 174, 127, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 208, 214, 179, 255);
			}
			break;
		case TileType::water:
			SDL_SetRenderDrawColor(renderer, 0, 0, 180, 255);
			break;
		case TileType::grass:
			SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
			break;
		default:
			break;
		}
		
		SDL_Rect rect = { t.x * tileSize, t.y * tileSize, tileSize, tileSize };
		SDL_RenderFillRect(renderer, &rect);
	}
}

// SDL_SetRenderDrawColor(renderer, 170, 174, 127, 255);
// SDL_SetRenderDrawColor(renderer, 208, 214, 179, 255);
// SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
// SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
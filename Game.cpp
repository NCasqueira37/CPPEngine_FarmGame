#include "Game.h"
#include <iostream>
#include "Level.h"

Level level;
Game::Game(SDL_Window* window, SDL_Renderer* renderer, int width, int height) {
	if (window != nullptr || renderer != nullptr) {
		// Create tiles
		level.createTiles(width, height, 50);

		// Main loop
		running = true;
		while (running) {
			processEvents(running);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			draw(renderer, width, height);
			SDL_RenderPresent(renderer);
		}
	}
	else {
		// If window or pointer is a null pointer
		std::cout << SDL_GetError() << std::endl;
	}
}

Game::~Game() {
	running = false;
}

void Game::update(double deltaTime) {
	
}

void Game::processEvents(const bool running) {
	if (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event) > 0) {
			if (event.type == SDL_QUIT) {
				this->running = false;
			}

			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_1:
					level.selectedTile = TileType::background;
					break;
				case SDL_SCANCODE_2:
					level.selectedTile = TileType::water;
					break;
				case SDL_SCANCODE_3:
					level.selectedTile = TileType::grass;
					break;
				default:
					break;
				}
			}
		}

		// setting tile Id
		int x, y;
		Uint32 mouseState = SDL_GetMouseState(&x, &y);
		if (mouseState == 1) {
			for (Tile& t : level.tiles) {

				int xTileSize = t.x * t.tileSize;
				int yTileSize = t.y * t.tileSize;

				if (x > xTileSize && x < xTileSize + t.tileSize &&
					y > yTileSize && y < yTileSize + t.tileSize) {
					if (t.getTileId() != level.selectedTile) {
						t.setTileId(level.selectedTile);
						std::cout << "Tile changed to: " << t.getTileId() << std::endl;
					}

				}

			}
		}
	}
}

void Game::draw(SDL_Renderer* renderer, int width, int height) {
	level.drawTiles(renderer, width, height, 50);
}
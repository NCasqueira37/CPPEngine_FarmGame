#include "Game.h"

Level level;
TextureManager textureManager;
Game::Game(SDL_Window* window, SDL_Renderer* renderer, int width, int height, double targetFrameRate) {
	if (window != nullptr || renderer != nullptr) {
		// Create tiles
		level.createTiles(width, height, 50);

		// load Textures
		textureManager.loadTexture(renderer, "0", "Data/Sprites/flower.png");

		// delta time variables
		auto previousFrame = SDL_GetTicks64();
		auto currentFrame = SDL_GetTicks64();
		double deltaTime = 0;

		// Main loop
		running = true;
		while (running) {

			// Calculate deltatime
			currentFrame = SDL_GetTicks64();
			deltaTime = (currentFrame - previousFrame) / 1000.0f;

			// running everything based on target frame rate
			if (deltaTime > 1.0 / targetFrameRate) {
				update(deltaTime);
				previousFrame = currentFrame;
				processEvents(running);
				
				draw(renderer, width, height);
			}

			
		}
	}
	else {
		// If window or renderer is a null pointer
		std::cout << SDL_GetError() << std::endl;
	}
}


Game::~Game() {
	running = false;
}


void Game::update(double deltaTime) {
	 Tile::updateTileWet(level);
}


void Game::processEvents(const bool running) {
	if (running) {

		SDL_Event event;
		while (SDL_PollEvent(&event) > 0) {

			// Quit window button
			if (event.type == SDL_QUIT) {
				this->running = false;
			}

			// Keyboard events
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
		handleTilePlacement();
		handlePlantPlacement();

	}
}


void Game::draw(SDL_Renderer* renderer, int width, int height) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	level.drawTiles(renderer, width, height, 50);
	for (auto& p : Plant::plants) {
		p.drawPlant(renderer, textureManager);
	}
	SDL_RenderPresent(renderer);
}


// Function to place tiles
void Game::handleTilePlacement() {
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	if (mouseState == SDL_BUTTON_LEFT) {
		for (Tile& t : level.tiles) {

			int xTileSize = t.x * t.tileSize;
			int yTileSize = t.y * t.tileSize;

			if (x > xTileSize && x < xTileSize + t.tileSize &&
				y > yTileSize && y < yTileSize + t.tileSize) {

				// Cannot place duplicate tile
				if (t.getTileType() != level.selectedTile) {
					// placing any tile on a wet tile
					if (t.getTileType() == TileType::wet) {
						t.setTileType(level.selectedTile);
						Tile::setTileWet(t, level);
					}
					// delete wet tiles after removing water tile
					else if (t.getTileType() == TileType::water) {
						t.setTileType(level.selectedTile);
						int distance = 1;
						for (int x1 = t.x - distance; x1 <= t.x + distance; x1++) {
							for (int y1 = t.y - distance; y1 <= t.y + distance; y1++) {
								for (Tile& t1 : level.tiles) {
									if (t1.getTileType() == TileType::wet) {
										if (t1.x == x1 && t1.y == y1) {
											t1.setTileType(TileType::grass);
										}
									}
								}
							}
						}
					}
					// can't place tile on a wet tile
					else if (t.getTileType() != TileType::wet) {
						t.setTileType(level.selectedTile);
						Tile::setTileWet(t, level);
					}
				}
			}
		}
	}
}


// Function to place plants
void Game::handlePlantPlacement() {
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);
	if (mouseState == SDL_BUTTON_X1) {
		for (Tile& t : level.tiles) {

			int xTileSize = t.x * t.tileSize;
			int yTileSize = t.y * t.tileSize;

			if (x > xTileSize && x < xTileSize + t.tileSize &&
				y > yTileSize && y < yTileSize + t.tileSize) {
				if (t.getTileType() == TileType::wet && t.hasPlant == false) {
					Plant p(xTileSize, yTileSize, "0", 50);
					t.hasPlant = true;
					std::cout << "Added plant\n";
				}
			}
		}
	}
}
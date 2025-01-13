#include "Game.h"

GameManager gameManager;
TextureManager textureManager;
Game::Game() {
	init();
}


void Game::init() {

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			std::cout << SDL_GetError() << std::endl;
		}
		else {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

			// Create tiles
			Tile::createTiles(width, height, 50, gameManager.tiles);

			// Testing
			
			textureManager.loadTexture("flower1", "Data/flower.png", renderer);

			// Main Loop
			running = true;
			SDL_Event event{};
			while (running) {
				// DeltaTime
				// update
				SDL_RenderClear(renderer);
				for (Tile& t : gameManager.tiles) {
					t.draw(renderer, 50);
					
				}
				for (Plant& p : gameManager.plants) {
					p.draw(renderer);
				}

				SDL_RenderPresent(renderer);
				// handle inputs
				
				// handle events
				handleEvents(event);
			}
			SDL_DestroyRenderer(renderer);
		}
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}


void Game::handleEvents(SDL_Event& e) {
	SDL_PollEvent(&e);
	handleInput(e);
	if (e.type == SDL_QUIT) {
		running = false;
	}
}


void Game::handleInput(SDL_Event& e) {
	int x, y;
	Uint32 mouseState = SDL_GetMouseState(&x, &y);

	// Place tiles with LMB
	if (mouseState == SDL_BUTTON_LEFT) {
		Tile::placeTile(x, y, 50, gameManager.selectedTileType, gameManager.tiles, gameManager.plants);
	}

	// Place plants with RMB
	if (mouseState == SDL_BUTTON_X1) {
		Plant p(x, y, 50, textureManager.textures["flower1"], gameManager.plants, gameManager.tiles);
	}

	// Keys to change selected tiles and plants
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.scancode)
		{
		case SDL_SCANCODE_1:
			gameManager.selectedTileType = Tile::TileType::background;
			std::cout << "Selected tile changed\n";
			break;

		case SDL_SCANCODE_2:
			gameManager.selectedTileType = Tile::TileType::grass;
			std::cout << "Selected tile changed\n";
			break;

		case SDL_SCANCODE_3:
			gameManager.selectedTileType = Tile::TileType::water;
			std::cout << "Selected tile changed\n";
			break;

		default:
			break;
		}
	}
}
#include <iostream>
#include "SDL.h"
#include "Game.h"
#include "Vector2D.h"

int main(int argc, char* argv[])
{
	// Variables
	std::string windowTitle = "SDL Window";
	int windowWidth = 800;
	int windowHeight = 600;
	double targetFrameRate = 60;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error: ";
		std::cout << SDL_GetError();
		SDL_Quit();
	}
	else {
		window = SDL_CreateWindow(windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
		
		if (window == nullptr) {
			std::cout << SDL_GetError() << std::endl;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				std::cout << SDL_GetError() << std::endl;
			}
			else {
				// For transparent graphics
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

				// Anti-Aliasing
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

				// render Driver
				SDL_RendererInfo rendererInfo;
				SDL_GetRendererInfo(renderer, &rendererInfo);
				std::cout << "Renderer = " << rendererInfo.name << std::endl;

				// Start Game
				Game game(window, renderer, windowWidth, windowHeight, targetFrameRate);

				// Destroy Renderer 
				SDL_DestroyRenderer(renderer);
			}
		}
		SDL_DestroyWindow(window);
	}
	SDL_Quit();

	return 0;
}
#pragma once
#include <iostream>
#include "SDL.h"
#include "GameManager.h"
#include "TextureManager.h"

#define title "SDL Window"
#define xPos SDL_WINDOWPOS_CENTERED
#define yPos SDL_WINDOWPOS_CENTERED
#define width 800
#define height 600

class Game
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = false;

public:
	Game();
	void init();
	void handleEvents(SDL_Event& e);
	void handleInput(SDL_Event& e);
};


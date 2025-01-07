#pragma once
#include "SDL.h"
#include <iostream>
#include "Level.h"
#include "Plant.h"
#include "TextureManager.h"

class Game
{
	void update(double deltaTime);
	void processEvents(const bool running);
	void draw(SDL_Renderer* renderer, int width, int height);
public:
	bool running = false;
	Game(SDL_Window* window, SDL_Renderer* renderer, int width, int height, double targetFrameRate);
	~Game();
};


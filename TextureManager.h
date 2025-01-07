#pragma once
#include <string>
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class TextureManager
{
	std::unordered_map<std::string, SDL_Texture*> textures;

public:
	TextureManager() = default;

	bool loadTexture(SDL_Renderer* renderer, const std::string& id, const std::string& fileName);
	SDL_Texture* getTexture(const std::string& id);
	void unloadTexture(const std::string& id);
};


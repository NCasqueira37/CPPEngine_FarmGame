#pragma once
#include <unordered_map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{

public:
	TextureManager() = default;

	std::unordered_map<std::string, SDL_Texture*> textures;

	void loadTexture(std::string textureName, std::string fileName, SDL_Renderer* renderer);
};


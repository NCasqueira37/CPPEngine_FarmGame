#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "SDL.h"


class TextureLoader
{
	static std::unordered_map<std::string, SDL_Texture*> textures;
public:
	static void loadTexture(SDL_Renderer* renderer, std::string fileName, std::string textureName);
	static void deallocateTextures();
};


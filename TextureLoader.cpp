#include "TextureLoader.h"


void TextureLoader::loadTexture(SDL_Renderer* renderer, std::string fileName, std::string textureName) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());

	if (surface != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture != nullptr) {
			textures.insert(std::make_pair(textureName, texture));
			
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

			SDL_FreeSurface(surface);
		}
	}
}

void TextureLoader::deallocateTextures() {
	while (!textures.empty()) {
		auto i = textures.begin();
		if (i->second != nullptr) {
			SDL_DestroyTexture(i->second);
		}
		textures.erase(i);
	}
}
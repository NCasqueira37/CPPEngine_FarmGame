#include "TextureManager.h"


bool TextureManager::loadTexture(SDL_Renderer* renderer, const std::string& id, const std::string& fileName) {
	SDL_Texture* texture = nullptr;
	
	texture = IMG_LoadTexture(renderer, fileName.c_str());
	if (texture == nullptr) {
		
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::cout << "Texture Loaded\n";
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		textures.insert(std::make_pair(id, texture));
		return true;
	}
}


SDL_Texture* TextureManager::getTexture(const std::string& id) {
	return (textures.contains(id) ? textures[id] : nullptr);
}


void TextureManager::unloadTexture(const std::string& id) {
	if (textures.contains(id)) {
		SDL_DestroyTexture(textures.at(id));
		textures.erase(id);
	}
}
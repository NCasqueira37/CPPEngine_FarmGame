#include "TextureManager.h"


void TextureManager::loadTexture(std::string textureName, std::string filePath, SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;

	// Load texture from filepath
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	// Set the blend mode so the texture can handle transparency
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	// Add texture to map
	textures.insert(std::make_pair(textureName.c_str(), texture));
}
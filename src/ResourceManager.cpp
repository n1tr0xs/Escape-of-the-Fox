#include "ResourceManager.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
	for (auto& pair : m_textures) {
		SDL_DestroyTexture(pair.second);
	}
}

SDL_Texture* ResourceManager::loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
	// Check if texture already loaded
	auto it = m_textures.find(filePath);
	if (it != m_textures.end()) {
		return it->second;
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
	if (!texture) {
		SDL_Log("Failed to load texture: %s", SDL_GetError());
		return nullptr;
	}

	m_textures[filePath] = texture;
	return texture;
}


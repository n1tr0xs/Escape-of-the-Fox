#include "ResourceManager.h"

#include <string>
#include <format>

ResourceManager::ResourceManager(SDL_Renderer* renderer) :
	m_renderer(renderer){}

ResourceManager::~ResourceManager() {
	SDL_Log("Destructing ResourceManager.");
	SDL_Log("\tDestructing m_textures.");
	for (auto& pair : m_textures) {
		SDL_DestroyTexture(pair.second);
	}
	
	SDL_Log("\tDestructing m_fonts.");
	for (auto& pair : m_fonts) {
		TTF_CloseFont(pair.second);
	}
	
}

SDL_Texture* ResourceManager::loadTexture(const std::string& filePath) {
	// Check if texture already loaded
	auto it = m_textures.find(filePath);
	if (it != m_textures.end()) {
		return it->second;
	}

	SDL_Texture* texture = IMG_LoadTexture(m_renderer, filePath.c_str());
	if (!texture) {
		SDL_Log("Failed to load texture: %s", SDL_GetError());
		return nullptr;
	}

	m_textures[filePath] = texture;
	return texture;
}

SDL_Texture* ResourceManager::loadLevelRelatedTexture(const std::string& fileName, const int levelNum) {
	return loadTexture(std::format("assets/level_{:02d}/{}", levelNum, fileName));
}

TTF_Font* ResourceManager::loadFont(const std::string& filePath) {
	auto it = m_fonts.find(filePath);
	if (it != m_fonts.end()) {
		return it->second;
	}

	TTF_Font* font = TTF_OpenFont(filePath.c_str(), 36);
	if (!font) {
		SDL_Log("Failed to load font: %s", SDL_GetError());
	}
	m_fonts[filePath] = font;
	return font;
}


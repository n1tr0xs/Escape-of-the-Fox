#include <format>
#include <string>

#include "constants.hpp"
#include "ResourceManager.hpp"

ResourceManager::ResourceManager(SDL_Renderer* renderer) :
	m_renderer{ renderer } {}

ResourceManager::~ResourceManager() {
	for (auto& pair : m_textures) {
		if (pair.second) {
			SDL_DestroyTexture(pair.second);
		}
	}

	for (auto& pair : m_fonts) {
		if (pair.second) {
			TTF_CloseFont(pair.second);
		}
	}

}

SDL_Texture* ResourceManager::loadTexture(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	return loadTextureInternal(filePath);
}

SDL_Texture* ResourceManager::loadTexture(const std::string& fileName, int levelNum) {
	std::string filePath = std::format(LEVEL_ASSET_PATH, levelNum, fileName);
	return loadTextureInternal(filePath);
}

TTF_Font* ResourceManager::loadFont(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	// Check if font already loaded
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

Mix_Music* ResourceManager::loadSound(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	// Check if font already loaded
	auto it = m_sounds.find(filePath);
	if (it != m_sounds.end()) {
		return it->second;
	}

	Mix_Music* sound = Mix_LoadMUS(filePath.c_str());
	if (!sound) {
		SDL_Log("Failed to load sound: %s", SDL_GetError());
	}
	m_sounds[filePath] = sound;
	return sound;
}

SDL_Texture* ResourceManager::loadTextureInternal(const std::string& filePath) {
	auto it = m_textures.find(filePath);
	// Check if texture already loaded
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
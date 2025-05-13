#include <format>
#include <string>

#include "constants.hpp"
#include "ResourceManager.hpp"

ResourceManager::ResourceManager(SDL_Renderer* renderer) :
	m_renderer{ renderer } {}

ResourceManager::~ResourceManager() {}

shared_SDL_Texture ResourceManager::loadTexture(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	return loadTextureInternal(filePath);
}

shared_SDL_Texture ResourceManager::loadTexture(const std::string& fileName, int levelNum) {
	std::string filePath = std::format(LEVEL_ASSET_PATH, levelNum, fileName);
	return loadTextureInternal(filePath);
}

shared_TTF_Font ResourceManager::loadFont(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	// Check if font already loaded
	auto it = m_fonts.find(filePath);
	if (it != m_fonts.end()) {
		return it->second;
	}

	shared_TTF_Font font(
		TTF_OpenFont(filePath.c_str(), 36),
		[](TTF_Font* p) {if (p) TTF_CloseFont(p); p = nullptr;}
	);
	if (!font) {
		SDL_Log("Failed to load font: %s", SDL_GetError());
	}
	m_fonts[filePath] = font;
	return font;
}

shared_Mix_Chunk ResourceManager::loadSound(const std::string& fileName) {
	std::string filePath = std::format(ASSET_PATH, fileName);
	// Check if font already loaded
	auto it = m_sounds.find(filePath);
	if (it != m_sounds.end()) {
		return it->second;
	}

	shared_Mix_Chunk sound(
		Mix_LoadWAV(filePath.c_str()),
		[](Mix_Chunk* p) {if (p) Mix_FreeChunk(p); p = nullptr;}
	);
	if (!sound) {
		SDL_Log("Failed to load sound: %s", SDL_GetError());
	}
	m_sounds[filePath] = sound;
	return sound;
}

shared_SDL_Texture ResourceManager::loadTextureInternal(const std::string& filePath) {
	auto it = m_textures.find(filePath);
	// Check if texture already loaded
	if (it != m_textures.end()) {
		return it->second;
	}

	shared_SDL_Texture texture(
		IMG_LoadTexture(m_renderer, filePath.c_str()),
		[](SDL_Texture* p) {if (p) SDL_DestroyTexture(p); p = nullptr;}
	);
	if (!texture) {
		SDL_Log("Failed to load texture: %s", SDL_GetError());
		return nullptr;
	}

	m_textures[filePath] = texture;
	return texture;
}
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
//#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

#include "smart_SDL.hpp"

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);
	
	// Loads texture
	shared_SDL_Texture loadTexture(const std::string& fileName);
	// Loads texture for given level
	shared_SDL_Texture loadTexture(const std::string& fileName, int levelNum);
	// Loads font
	shared_TTF_Font loadFont(const std::string& filePath);
	// Loads sound
	//shared_Mix_Chunk loadSound(const std::string& filePath);

private:
	shared_SDL_Texture loadTextureInternal(const std::string& filePath);

	SDL_Renderer* m_renderer;
	std::unordered_map<std::string, shared_SDL_Texture> m_textures;
	std::unordered_map<std::string, shared_TTF_Font> m_fonts;
	//std::unordered_map<std::string, shared_Mix_Chunk> m_sounds;
};
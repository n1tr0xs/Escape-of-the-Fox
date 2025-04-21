#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();

	SDL_Texture* loadTexture(const std::string& filePath);
	TTF_Font* loadFont(const std::string& filePath);

private:
	SDL_Renderer* m_renderer;
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<std::string, TTF_Font*> m_fonts;
};
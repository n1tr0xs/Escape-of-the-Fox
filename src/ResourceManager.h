#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);

private:
	std::unordered_map<std::string, SDL_Texture*> m_textures;
};
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <memory>

#include "ResourceManager.h"

class Level {
public:
	Level(SDL_Texture* texture);

	void render(SDL_Renderer* renderer);
	void update(Uint64 deltaTime);

	bool isSolidAtPixel(float x, float y);
private:	
	SDL_Texture* m_texture;
	std::vector<std::vector<Uint8>> m_tileMap;
	
	void addRow(Uint8 block);
	void addRows(int rows, Uint8 block);
};
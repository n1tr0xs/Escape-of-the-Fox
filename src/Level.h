#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <memory>

#include "constants.h"
#include "ResourceManager.h"

class Level {
public:
	Level(SDL_Texture* texture);

	void render(SDL_Renderer* renderer);
	void update(Uint64 deltaTime);

	bool isSolidAtPixel(float x, float y);
	bool isSolidVertically(float x, float topY, float bottomY);
	bool isSolidHorizontally(float y, float leftX, float rightX);

private:
	SDL_Texture* m_texture;
	std::vector<std::vector<Uint8>> m_tileMap;

	void addRow(Uint8 block);
	void addRows(int rows, Uint8 block);
	void renderGrid(SDL_Renderer* renderer);
	void renderTextures(SDL_Renderer* renderer);

	void fillWith(int startX, int startY, int endX, int endY, Uint8 block);
};
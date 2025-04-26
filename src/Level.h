#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <memory>

#include "constants.h"
#include "ResourceManager.h"
#include "Camera.h"

using Tile = int;

class Level {
public:
	Level(SDL_Texture* texture);

	void render(SDL_Renderer* renderer, SDL_FRect cameraRect);
	void handleEvent(const SDL_Event& event);
	void update(Uint64 deltaTime);
	bool loadFromFile(const std::string& filePath);

	bool isSolidAtPixel(float x, float y);
	bool isSolidVertically(float x, float topY, float bottomY);
	bool isSolidHorizontally(float y, float leftX, float rightX);

	float getMapHeightInPixels();
	float getMapWidthInPixels();
private:
	SDL_Texture* m_texture;
	std::vector<std::vector<Tile>> m_tileMap;

	void addRow(Tile block);
	void addRows(int rows, Tile block);
	void renderGrid(SDL_Renderer* renderer);
	void renderTextures(SDL_Renderer* renderer, SDL_FRect cameraRect);

	void fillWith(int startX, int startY, int endX, int endY, Tile block);
};
#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

#include "Camera.hpp"
#include "constants.hpp"
#include "ResourceManager.hpp"


using Tile = int;

class Level {
public:
	Level(SDL_Texture* texture, SDL_Texture* backgroundStaticTexture, SDL_Texture* backgroundBackTexture, SDL_Texture* backgroundFrontTexture);

	void render(SDL_Renderer* renderer, SDL_FRect cameraRect);
	void handleEvent(const SDL_Event& event);
	void update(const Uint64 deltaTime);
	bool loadFromFile(const std::string& filePath);

	bool isSolidAtPixel(float x, float y);
	bool isSolidVertically(float x, float topY, float bottomY);
	bool isSolidHorizontally(float y, float leftX, float rightX);

	float getMapHeightInPixels();
	float getMapWidthInPixels();
private:
	SDL_Texture* m_texture;
	SDL_Texture* m_backgroundStaticTexture;
	SDL_Texture* m_backgroundBackTexture;
	SDL_Texture* m_backgroundFrontTexture;
	std::vector<std::vector<Tile>> m_tileMap;

	void addRow(Tile block);
	void addRows(int rows, Tile block);
	void renderGrid(SDL_Renderer* renderer);
	void renderTextures(SDL_Renderer* renderer, SDL_FRect cameraRect);
	void renderBackground(SDL_Renderer* renderer, SDL_FRect cameraRect);

	void fillWith(int startX, int startY, int endX, int endY, Tile block);
};
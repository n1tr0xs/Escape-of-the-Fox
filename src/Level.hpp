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
	Level(int levelNum, shared_SDL_Texture texture, shared_SDL_Texture backgroundStaticTexture, shared_SDL_Texture backgroundBackTexture, shared_SDL_Texture backgroundFrontTexture);

	// Renders Level regarding to cameraRect
	void render(SDL_Renderer* renderer, SDL_FRect cameraRect);

	// Checks pixel solidity
	bool isSolidAtPixel(float x, float y);
	// Checks vertical wall solidity
	bool isSolidVertically(float x, float topY, float bottomY);
	// Checks horizontal platform solidity
	bool isSolidHorizontally(float y, float leftX, float rightX);

	// Getters
	float getMapHeightInPixels();
	float getMapWidthInPixels();
private:
	// Loads level from file
	bool loadFromFile(const std::string& filePath);
	// Renders tilemap
	void renderTiles(SDL_Renderer* renderer, SDL_FRect cameraRect);
	// Renders background
	void renderBackground(SDL_Renderer* renderer, SDL_FRect cameraRect);

	shared_SDL_Texture m_texture;
	shared_SDL_Texture m_backgroundStaticTexture;
	shared_SDL_Texture m_backgroundBackTexture;
	shared_SDL_Texture m_backgroundFrontTexture;
	std::vector<std::vector<Tile>> m_tileMap;
};
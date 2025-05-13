#include <fstream>
#include <iostream>
#include <format>
#include <sstream>
#include <string>
#include <vector>

#include "Level.hpp"

Level::Level(int levelNum, shared_SDL_Texture texture, shared_SDL_Texture backgroundStaticTexture, shared_SDL_Texture backgroundBackTexture, shared_SDL_Texture backgroundFrontTexture) :
	m_texture{ texture }, m_backgroundStaticTexture{ backgroundStaticTexture }, m_backgroundBackTexture{ backgroundBackTexture }, m_backgroundFrontTexture{ backgroundFrontTexture } {
	
	std::string filePath = std::format(LEVEL_ASSET_PATH, levelNum, "tilemap.txt");
	loadFromFile(filePath);
}

void Level::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	renderBackground(renderer, cameraRect);
	renderTiles(renderer, cameraRect);
}

void Level::renderBackground(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	float scale = static_cast<float>(RENDERER_HEIGHT_IN_PIXELS) / m_backgroundBackTexture->h;

	float mapWidth = getMapWidthInPixels();
	float mapHeight = getMapHeightInPixels();

	SDL_FRect destStatic = {
		0,
		0,
		RENDERER_WIDTH_IN_PIXELS,
		RENDERER_HEIGHT_IN_PIXELS,
	};
	SDL_RenderTexture(renderer, m_backgroundStaticTexture.get(), NULL, &destStatic);

	float backSpeed = 4;
	SDL_FRect destBack = {
		0 - cameraRect.x / backSpeed,
		0 - cameraRect.y / backSpeed,
		mapWidth,
		mapHeight,
	};
	SDL_RenderTextureTiled(renderer, m_backgroundBackTexture.get(), NULL, scale, &destBack);

	float frontSpeed = 2;
	SDL_FRect destFront = {
		0 - cameraRect.x / frontSpeed,
		0 - cameraRect.y / frontSpeed,
		mapWidth,
		mapHeight,
	};
	SDL_RenderTextureTiled(renderer, m_backgroundFrontTexture.get(), NULL, scale, &destFront);
}

void Level::renderTiles(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	SDL_FRect src = { 0.0f, 0.0f, TILE_SIZE, TILE_SIZE };
	SDL_FRect dest = { 0.0f, 0.0f, TILE_SIZE, TILE_SIZE };
	for (size_t row = 0; row < m_tileMap.size(); ++row) {
		dest.y = row * TILE_SIZE - cameraRect.y;
		for (size_t col = 0; col < m_tileMap[row].size(); ++col) {
			dest.x = col * TILE_SIZE - cameraRect.x;
			Tile tile = m_tileMap[row][col];
			if (tile == 0)
				continue;
			src.x = static_cast<float>(tile * TILE_SIZE);
			SDL_RenderTexture(renderer, m_texture.get(), &src, &dest);
		}
	}
}

bool Level::loadFromFile(const std::string& filePath) {
	m_tileMap.clear();
	std::ifstream file(filePath);
	if (!file.is_open()) {
		SDL_Log("Failed to open level file: %s", filePath.c_str());
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<Tile> row;
		std::stringstream ss(line);
		Tile tile;
		while (ss >> tile) {
			row.push_back(tile);
		}
		m_tileMap.push_back(row);
	}
	file.close();
	return true;
}

bool Level::isSolidAtPixel(float x, float y) {
	int tileX = static_cast<int>(x / TILE_SIZE);
	int tileY = static_cast<int>(y / TILE_SIZE);

	if (tileY < 0)
		return false;
	if (tileX < 0)
		return false;

	if (tileY >= m_tileMap.size())
		return false;
	if (tileX >= m_tileMap[0].size())
		return false;

	if (m_tileMap[tileY][tileX] == 0)
		return false;

	return true;
}

bool Level::isSolidVertically(float x, float topY, float bottomY) {
	if (x < 0) {
		return true;
	}
	for (float y = topY; y < bottomY; ++y) {
		if (isSolidAtPixel(x, y)) {
			return true;
		}
	}
	return false;
}

bool Level::isSolidHorizontally(float y, float leftX, float rightX) {
	for (float x = leftX; x < rightX; ++x) {
		if (isSolidAtPixel(x, y)) {
			return true;
		}
	}
	return false;
}

float Level::getMapHeightInPixels() {
	return static_cast<float>(m_tileMap.size() * TILE_SIZE);
}

float Level::getMapWidthInPixels() {
	return static_cast<float>(m_tileMap[0].size() * TILE_SIZE);
}
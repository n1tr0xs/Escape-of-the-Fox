#include "Level.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Level::Level(SDL_Texture* texture, SDL_Texture* backgroundStaticTexture, SDL_Texture* backgroundBackTexture, SDL_Texture* backgroundFrontTexture) :
	m_texture(texture), m_backgroundStaticTexture(backgroundStaticTexture), m_backgroundBackTexture(backgroundBackTexture), m_backgroundFrontTexture(backgroundFrontTexture) {}

void Level::addRow(Tile block) {
	m_tileMap.push_back(std::vector<Tile>(RENDERER_WIDTH_IN_TILES * 5, block));
}

void Level::addRows(int rows, Tile block) {
	for (int i = 0; i < rows; ++i) {
		addRow(block);
	}
}

void Level::renderGrid(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (float x = 0; x < RENDERER_WIDTH_IN_PIXELS; x += TILE_SIZE) {
		for (float y = 0; y < RENDERER_HEIGHT_IN_PIXELS; y += TILE_SIZE) {
			SDL_FRect rect = { x, y, TILE_SIZE, TILE_SIZE };
			SDL_RenderRect(renderer, &rect);
		}
	}
}

void Level::renderTextures(SDL_Renderer* renderer, SDL_FRect cameraRect) {
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
			SDL_RenderTexture(renderer, m_texture, &src, &dest);
		}
	}
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
	SDL_RenderTexture(renderer, m_backgroundStaticTexture, NULL, &destStatic);

	float backSpeed = 4;
	SDL_FRect destBack = {
		0 - cameraRect.x / backSpeed,
		0 - cameraRect.y / backSpeed,
		mapWidth,
		mapHeight,
	};
	SDL_RenderTextureTiled(renderer, m_backgroundBackTexture, NULL, scale, &destBack);

	float frontSpeed = 2;
	SDL_FRect destFront = {
		0 - cameraRect.x / frontSpeed,
		0 - cameraRect.y / frontSpeed,
		mapWidth,
		mapHeight,
	};
	SDL_RenderTextureTiled(renderer, m_backgroundFrontTexture, NULL, scale, &destFront);
}

void Level::fillWith(int startX, int startY, int endX, int endY, Tile block) {
	if (startY < 0 || startX < 0)
		return;
	if (endY >= m_tileMap.size() || endX >= m_tileMap[0].size())
		return;
	for (int x = startX; x <= endX; ++x) {
		for (int y = startY; y <= endY; ++y) {
			m_tileMap[y][x] = block;
		}
	}
}

void Level::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	renderGrid(renderer);
	renderBackground(renderer, cameraRect);
	renderTextures(renderer, cameraRect);
}

void Level::handleEvent(const SDL_Event& event) {}

void Level::update(Uint64 deltaTime) {}

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

#include "Level.h"

#include "Player.h"

Level::Level(SDL_Texture* texture) :
	m_texture(texture) {

	addRows(13, 0);
	addRows(2, 1);
	addRows(1, 2);

	// Horizontal platform
	fillWith(5, 8, 7, 8, 1);
	
	// Wall
	fillWith(15, 10, 15, 12, 1);	
}

void Level::addRow(Uint8 block) {
	m_tileMap.push_back(std::vector<Uint8>(RENDERER_WIDTH_IN_TILES, block));
}

void Level::addRows(int rows, Uint8 block) {
	for (int i = 0; i < rows; ++i)
		addRow(block);
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

void Level::renderTextures(SDL_Renderer* renderer) {
	SDL_FRect src = { 0.0f, 0.0f, TILE_SIZE, TILE_SIZE };
	SDL_FRect dest = { 0.0f, 0.0f, TILE_SIZE, TILE_SIZE };
	for (size_t row = 0; row < m_tileMap.size(); ++row) {
		dest.y = row * TILE_SIZE;
		for (size_t col = 0; col < m_tileMap[0].size(); ++col) {
			dest.x = col * TILE_SIZE;
			src.x = m_tileMap[row][col] * TILE_SIZE;
			SDL_RenderTexture(renderer, m_texture, &src, &dest);
		}
	}
}

void Level::fillWith(int startX, int startY, int endX, int endY, Uint8 block) {
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

void Level::render(SDL_Renderer* renderer) {
	renderGrid(renderer);
	renderTextures(renderer);
}

void Level::update(Uint64 deltaTime) {

}

bool Level::isSolidAtPixel(float x, float y) {
	int tileX = x / TILE_SIZE;
	int tileY = y / TILE_SIZE;

	if (tileY < 0)
		return false;
	if (tileX < 0)
		return false;

	if (tileY >= m_tileMap.size())
		return true;
	if (tileX >= m_tileMap[0].size())
		return false;


	if (m_tileMap[tileY][tileX] == 0)
		return false;

	return true;
}

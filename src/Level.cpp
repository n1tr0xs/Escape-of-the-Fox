#include "Level.h"

#include "Player.h"

Level::Level(SDL_Texture* texture) :
	m_texture(texture) {

	addRows(2, 1);
	addRows(1, 2);

	
}

void Level::addRow(Uint8 block) {
	int rowLength = 1920 / 32 * 6;
	m_tileMap.push_back(std::vector<Uint8>(rowLength, block));
}

void Level::addRows(int rows, Uint8 block) {
	for (int i = 0; i < rows; ++i)
		addRow(block);
}

void Level::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (float x = 0; x < RENDERER_WIDTH_IN_PIXELS; x += TILE_SIZE) {
		for (float y = 0; y < RENDERER_HEIGHT_IN_PIXELS; y += TILE_SIZE) {
			SDL_FRect rect = { x, y, TILE_SIZE, TILE_SIZE };
			SDL_RenderRect(renderer, &rect);
		}
	}
}

void Level::update(Uint64 deltaTime) {
	
}

bool Level::isSolidAtPixel(float x, float y) {
	return false;
}

#include "Level.h"

Level::Level(SDL_Texture* texture) :
	m_texture(texture) {
	addRows(20, 0);
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
	int tileSize = 32;

	int w, h;
	SDL_GetRenderOutputSize(renderer, &w, &h);

	SDL_FRect src = { 0, 0, tileSize, tileSize };
	SDL_FRect dest = { 0, 0, tileSize, tileSize };

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (size_t col = 0; col < w / tileSize+1; ++col) {
		dest.x = col * tileSize;
		for (size_t row = 0; row < h / tileSize+1; ++row) {
			dest.y = row * tileSize;
			SDL_RenderRect(renderer, &dest);
		}
	}
}
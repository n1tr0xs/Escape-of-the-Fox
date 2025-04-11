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
	int tileSize = 32;

	int w, h;
	SDL_GetRenderOutputSize(renderer, &w, &h);

	SDL_FRect src = { 0, 0, tileSize, tileSize };
	SDL_FRect dest = { 0, h-tileSize, tileSize, tileSize };

	// Rendering grid
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (size_t col = 0; col < w / tileSize+1; ++col) {
		dest.x = col * tileSize;
		for (size_t row = 0; row < h / tileSize+1; ++row) {
			dest.y = row * tileSize;
			SDL_RenderRect(renderer, &dest);
		}
	}

	//// Rendering level payload from bottom to top
	//for (int row = m_tileMap.size() - 1; row >= 0; --row) {
	//	dest.x = 0;
	//	for (int col = m_tileMap[0].size() - 1; col >= 0; --col) {
	//		src.x = m_tileMap[row][col] * tileSize;
	//		src.y = 0;
	//		SDL_RenderTexture(renderer, m_texture, &src, &dest);
	//		dest.x += tileSize;
	//	}
	//	dest.y -= tileSize;
	//}
	//payload_min_y = dest.y;
	//// Rendering empty tiles as background
	//src.x = 0;
	//src.y = 0;
	//while (dest.y > 0) {
	//	for (int x = 0.0f; x < w; x += tileSize) {
	//		dest.x = x;
	//		SDL_RenderTexture(renderer, m_texture, &src, &dest);
	//	}
	//	dest.y -= tileSize;
	//}

	
}

void Level::update(Uint64 deltaTime) {
	
}

bool Level::isSolidAtPixel(float x, float y) {
	return false;
}

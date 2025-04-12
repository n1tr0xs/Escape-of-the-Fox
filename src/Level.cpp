#include "Level.h"

#include "Player.h"

Level::Level(SDL_Texture* texture) :
	m_texture(texture) {

	addRows(13, 0);
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
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (float x = 0; x < RENDERER_WIDTH_IN_PIXELS; x += TILE_SIZE) {
		for (float y = 0; y < RENDERER_HEIGHT_IN_PIXELS; y += TILE_SIZE) {
			SDL_FRect rect = { x, y, TILE_SIZE, TILE_SIZE };
			SDL_RenderRect(renderer, &rect);
		}
	}*/
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

void Level::update(Uint64 deltaTime) {

}

bool Level::isSolidAtPixel(float x, float y) {
	return false;
}

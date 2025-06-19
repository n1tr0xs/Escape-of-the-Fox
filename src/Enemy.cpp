#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Entity{ x, y, width, height, texture } {}

void Enemy::update(const Uint64 deltaTime) {}

void Enemy::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	const SDL_FRect rect = {
		getX() - cameraRect.x,
		getY() - cameraRect.y,
		getWidth(),
		getHeight()
	};
	SDL_SetRenderDrawColor(renderer, 70, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}



#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float width, float height, SDL_Texture* texture) :
	Entity{ x, y, width, height, texture } {}

void Enemy::update(const Uint64 deltaTime) {}

void Enemy::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	const SDL_FRect rect = {
		m_rect.x - cameraRect.x,
		m_rect.y - cameraRect.y,
		m_rect.w,
		m_rect.h
	};
	SDL_SetRenderDrawColor(renderer, 70, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}


